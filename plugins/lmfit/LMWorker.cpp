#pragma hdrstop
#include "rrRoadRunnerData.h"
#include "rrLogger.h"
#include "LMWorker.h"
#include "lm.h"
#include "lib/lmmin.h"
#include "rrStringUtils.h"
#include "rrUtils.h"
#include "rrProperty.h"

//Todo: no reason using the roaddrunner C API here, convert an usse the CPP api directly
#include "../../wrappers/C/rrc_api.h"
#include "../../wrappers/C/rrc_utilities.h"
#include "../../wrappers/C/rrc_cpp_support.h"
//---------------------------------------------------------------------------
namespace lmfit
{
using namespace rr;
using namespace rrc;
using namespace std;

LMWorker::LMWorker(LM& host)
:
mTheHost(host),
mRRI(NULL)
{
    memset(&mLMData, 0, sizeof(lmDataStructure));
}

bool LMWorker::isRunning() const
{
    return mThread.isRunning();
}

void LMWorker::start(bool runInThread)
{
    if(runInThread)
    {
        if(mThread.isRunning())
        {
            Log(lError)<<"Tried to start an already working thread!";
            return;
        }

        mThread.start(*this);    //Will spawn the run function below in a thread
    }
    else
    {
        run();
    }
}

void LMWorker::run()
{
    workerStarted();

    setupRoadRunner();

    StringList& species = mTheHost.mExperimentalDataSelectionList.getValueReference();//mMinData.getExperimentalDataSelectionList();
    Log(lInfo)<<"The following species are selected: "<<species.AsString();

    Properties& Paras =  mTheHost.mInputParameterList.getValueReference(); //mMinData.getProperties();
    Log(lInfo)<<"The following parameters are to be minimized";
    for(int i = 0; i < Paras.count(); i++)
    {
        Log(lInfo)<<Paras[i]->getName()<<" with initial value: "<<Paras[i]->getValueAsString();
    }

    mTheHost.mNrOfIter.setValue(0);
    mTheHost.mNorm.setValue(0.0);
    //Some parameters to the Algorithm..
    lm_control_struct control = lm_control_double;

    //Set defaults from Plugin
    control.ftol                    =       *(double*)  mTheHost.ftol.getValueHandle();
    control.xtol                    =       *(double*)  mTheHost.xtol.getValueHandle();
    control.gtol                    =       *(double*)  mTheHost.gtol.getValueHandle();
    control.epsilon                 =       *(double*)  mTheHost.epsilon.getValueHandle();
    control.stepbound               =       *(double*)  mTheHost.stepbound.getValueHandle();
    control.patience                =       *(int*)     mTheHost.patience.getValueHandle();
//    control.scale_diag              =       *(int*)     mTheHost.scale_diag.getValueHandle();

    control.msgfile = NULL;
    control.verbosity = 0;

    //Setup data structures
    setup();


    //This is the library function doing the minimization..
    lmmin(  mLMData.nrOfParameters,
            mLMData.parameters,
            mLMData.nrOfResiduePoints,
			(const void*) &mTheHost,
            evaluate,
            &control,
            &mTheHost.mLMStatus);

    //The user may have aborted the minization... check here..
    if(mTheHost.mTerminate)
    {
        //user did set the terminate flag to true.. discard any minimization data and get out of the
        //plugin execute code..
        Log(lInfo)<<"The minimization was terminated.. aborting";
        workerFinished();
        return;
    }
    /* print results */
    Log(lInfo)<<"==================== Fitting Result ================================";
    Log(lInfo)<<"Nr of function evaluations: "  <<  mTheHost.mLMStatus.nfev;
    Log(lInfo)<<"Status message: "              <<  lm_infmsg[mTheHost.mLMStatus.outcome];
    Log(lInfo)<<"Minimized parameter values: ";

    for (int i = 0; i < mLMData.nrOfParameters; ++i)
    {
        Log(lInfo)<<"Parameter "<<mLMData.parameterLabels[i]<<" = "<< mLMData.parameters[i];
    }

    Log(lInfo)<<"Norm:  "<<mTheHost.mLMStatus.fnorm;

    //Populate with data to report back
    Properties& parsOut = mTheHost.mOutputParameterList.getValueReference();
    parsOut.clear();
    for (int i = 0; i < mLMData.nrOfParameters; ++i)
    {
        parsOut.add(new Property<double>(mLMData.parameters[i], mLMData.parameterLabels[i], ""), true);
    }

    mTheHost.mNorm.setValue(mTheHost.mLMStatus.fnorm);
    createModelData(mTheHost.mModelData.getValuePointer());

    createResidualsData(mTheHost.mResidualsData.getValuePointer());
    workerFinished();
}

void LMWorker::workerStarted()
{
    mTheHost.mIsWorking = true;
    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, mTheHost.mWorkStartedData2);
    }
}

void LMWorker::workerFinished()
{
    mTheHost.mIsWorking = false;//Set this flag before event so client can query plugin about termination
    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent(mTheHost.mWorkFinishedData1, mTheHost.mWorkFinishedData2);
    }
}

bool LMWorker::setup()
{
    StringList& species         = mTheHost.mExperimentalDataSelectionList.getValueReference();   //Model data selection..
    mLMData.nrOfSpecies         = species.Count();
    Properties parameters       = mTheHost.mInputParameterList.getValue();
    mLMData.nrOfParameters      = parameters.count();
    mLMData.parameters          = new double[mLMData.nrOfParameters];
    mLMData.mLMPlugin           = static_cast<RRPluginHandle> (&mTheHost);
    //Set initial parameter values
    for(int i = 0; i < mLMData.nrOfParameters; i++)
    {
        Property<double> *par = (Property<double>*) parameters[i];
        if(par)
        {
            mLMData.parameters[i] = par->getValue();
        }
        else
        {
            throw("Bad stuff..");
        }
    }

    RoadRunnerData& obsData             = (mTheHost.mExperimentalData.getValueReference());
    mLMData.nrOfTimePoints              = obsData.rSize();
    mLMData.timeStart                   = obsData.getTimeStart();
    mLMData.timeEnd                     = obsData.getTimeEnd();
    mLMData.nrOfResiduePoints           = mLMData.nrOfSpecies * mLMData.nrOfTimePoints;
    mLMData.time                        = new double[mLMData.nrOfTimePoints];

    mLMData.experimentalData            = new double*[mLMData.nrOfSpecies];

    if(obsData.hasWeights())
    {
        mLMData.experimentalDataWeights = new double*[mLMData.nrOfSpecies];
    }

    mLMData.speciesLabels               = new char*[mLMData.nrOfSpecies];

    //Each species data points and label
    for (int i = 0; i < mLMData.nrOfSpecies; i++)
    {
        mLMData.experimentalData[i]     = new double[mLMData.nrOfTimePoints];
        mLMData.speciesLabels[i]        = createText(species[i]);

        if(obsData.hasWeights())
        {
            mLMData.experimentalDataWeights[i] = new double[mLMData.nrOfTimePoints];
        }
    }

    //Populate Experimental Data
    for (int i = 0; i < mLMData.nrOfSpecies; i++)
    {
        for(int timePoint = 0; timePoint < mLMData.nrOfTimePoints; timePoint++)
        {
            if(i == 0)
            {
                mLMData.time[timePoint] = obsData(timePoint, 0);
            }
            mLMData.experimentalData[i][timePoint] = obsData(timePoint, i + 1);
        }
    }

    //Populate weights..
    if(obsData.hasWeights())
    {
        for (int i = 0; i < mLMData.nrOfSpecies; i++)
        {
            for(int timePoint = 0; timePoint < mLMData.nrOfTimePoints; timePoint++)
            {
                mLMData.experimentalDataWeights[i][timePoint] = obsData.getWeight(timePoint, i + 1);
            }
        }
    }

    mLMData.parameterLabels           = new char*[mLMData.nrOfParameters];
    for (int i = 0; i < mLMData.nrOfParameters; i++)
    {
        mLMData.parameterLabels[i]     = createText(parameters[i]->getName());
    }

    mLMData.rrHandle                = mRRI;
    mRRI->setSelections(species);

    mLMData.mProgressEvent               = mTheHost.mWorkProgressEvent;
    mLMData.mProgressEventContextData    = mTheHost.mWorkProgressData1;
    return true;
}

bool LMWorker::setupRoadRunner()
{
    if(mRRI)
    {
        delete mRRI;
    }

    mRRI = new RoadRunner;
    mRRI->load(mTheHost.mSBML.getValue());
    mRRI->setSelections(mTheHost.getExperimentalDataSelectionList());
    return true;
}

/* function evaluation, determination of residues */
void evaluate(const double *par,       //Property vector
              int          m_dat,      //Dimension of residue vector
              const void   *userData,  //Data structure
              double       *fvec,      //residue vector..
              int          *userBreak  //Non zero value means termination
)
{
    const LM *thePlugin = (const LM*) userData;
    LM* plugin = const_cast<LM*>(thePlugin);
	const lmDataStructure* myData = &(thePlugin->mLMData);

    //Check if user have asked for termination..
    if(thePlugin->isBeingTerminated())
    {
        (*userBreak) = -1; //This signals lmfit algorithm to break
        return;
    }

    reset(myData->rrHandle);

    for(int i = 0; i < myData->nrOfParameters; i++)
    {
        setValue(myData->rrHandle, myData->parameterLabels[i], par[i]);
        Log(lDebug)<<myData->parameterLabels[i]<<" = "<<par[i]<<endl;
    }

    RRDataHandle rrData = simulateEx(   myData->rrHandle,
                                        myData->timeStart,
                                        myData->timeEnd,
                                        myData->nrOfTimePoints);

    if(!rrData)
    {
        char* lastError = getLastError();
        Log(lError)<<"Error in simulateEx: "<<lastError;
        rr::freeText(lastError);
        return;
    }

    RRCDataPtr rrcData = createRRCData( *((RoadRunnerData*) rrData));
    //calculate fvec for each specie
    int count = 0;
    for(int i = 0; i < myData->nrOfSpecies; i++)
    {
        fvec[count] = 0;
        for(int j = 0; j < myData->nrOfTimePoints; j++ )
        {
            double modelValue;
            if(!rrp::getRRCDataElement(rrcData, j, i, &modelValue))
            {
                throw("Bad stuff...") ;
            }

            if(!isNaN(myData->experimentalData[i][j]))
            {
                fvec[count] = myData->experimentalData[i][j] - modelValue;

                if(myData->experimentalDataWeights != NULL)
                {
                    if(myData->experimentalDataWeights[i][j] != 0) //Cause the first column is time... :( loks ugly
                    {
                        double weight =  myData->experimentalDataWeights[i][j];
                        fvec[count] = fvec[count] / weight;
                    }
                }
            }
            else
            {
                fvec[count] = 0;
            }
            count++;
        }
    }

    freeRRCData(rrcData);

    if(plugin->hasProgressEvent())
    {
        //Assign data relevant to the progress
        double norm = lm_enorm(m_dat, fvec);
		plugin->mNorm.setValue(norm);
        plugin->mNrOfIter.setValue(plugin->mNrOfIter.getValue() + 1);

        //Pass trough event data
        pair<void*, void*> passTroughData = plugin->getWorkProgressData();
        plugin->WorkProgressEvent(passTroughData.first, passTroughData.second);
    }
}

void LMWorker::createModelData(RoadRunnerData* _data)
{
    RoadRunnerData& data = *(_data);
    //We now have the parameters
    StringList selList("time");
    selList.Append(mTheHost.mModelDataSelectionList.getValue());

    data.reSize(mLMData.nrOfTimePoints, selList.Count());
    mRRI->reset();
    mRRI->setSelections(selList);

    for(int i = 0; i < mLMData.nrOfParameters; i++)
    {
        mRRI->setValue(mLMData.parameterLabels[i], mLMData.parameters[i]);
    }

    SimulateOptions options;
    options.start = mLMData.timeStart;
    options.duration = mLMData.timeEnd - mLMData.timeStart;
    options.steps = mLMData.nrOfTimePoints - 1;
    options.flags = options.flags | SimulateOptions::RESET_MODEL;

    if(mRRI->simulate(&options))
    {
         data = *mRRI->getSimulationResult();
    }
}

void LMWorker::createResidualsData(RoadRunnerData* _data)
{
    RoadRunnerData& resData = *(_data);        
    //We now have the parameters
    RoadRunnerData& obsData = (mTheHost.mExperimentalData.getValueReference());
    RoadRunnerData& modData = (mTheHost.mModelData.getValueReference());

    resData.reSize(modData.rSize(), modData.cSize());

    //setup coulumn names
    resData.setColumnNames(modData.getColumnNames());

    for(int sel = 0; sel < mLMData.nrOfSpecies + 1; sel++)    //selection 1 becuase of time column..
    {
        for(int i = 0; i < mLMData.nrOfTimePoints; i++)
        {
            if(sel == 0)
            {
                resData(i, sel) = modData(i, sel);    //Time
            }
            else
            {
                //The modData may contain data for other species than that was fitted..
                //We need to find out what coulmn correspond to what..
                string specie = obsData.getColumnName(sel);
                int colNr = modData.getColumnIndex(specie);
                if(colNr != -1)
                {
                    resData(i,sel) = obsData(i, sel) - modData(i, colNr);
                }
                else
                {
                    Log(lError)<<"Problem with column names when creating residual data!";
                }
            }
        }
    }
}

}
