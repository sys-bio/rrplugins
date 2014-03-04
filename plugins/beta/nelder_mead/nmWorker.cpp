#pragma hdrstop
#include "nmWorker.h"
#include "rr/rrRoadRunnerOptions.h"
#include "rr-libstruct/lsLA.h"
#include "rr/C/rrc_api.h" //Todo: no reason using the roaddrunner C API here, convert and use the CPP api directly
#include "rr/C/rrc_utilities.h"
#include "lib/nmsimplex.h"
#include "telLogger.h"
#include "telException.h"
#include "telTelluriumData.h"
#include "telUtils.h"
#include "telMathUtils.h"
#include "telProperty.h"
#include "telPluginManager.h"
#include "nmNelderMead.h"

//---------------------------------------------------------------------------
using namespace rrc;
using namespace std;
using namespace tlp;

nmWorker::nmWorker(NelderMead& host)
:
mHost(host),
mRRI(NULL)
{}

bool nmWorker::isRunning() const
{
    return mThread.isRunning();
}

void nmWorker::start(bool runInThread)
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

void nmWorker::run()
{
    workerStarted();

    setupRoadRunner();

    StringList& species = mHost.mExperimentalDataSelectionList.getValueReference();
    Log(lInfo)<<"The following species are selected: "<<species.AsString();

    Properties& Paras =  mHost.mInputParameterList.getValueReference();
    Log(lInfo)<<"The following parameters are to be minimized";
    for(int i = 0; i < Paras.count(); i++)
    {
        Log(lInfo)<<Paras[i]->getName()<<" with initial value: "<<Paras[i]->getValueAsString();
    }

    mHost.mNrOfIter.setValue(0);
    mHost.mNorm.setValue(0.0);
    //Some parameters to the Algorithm..

//    //Set defaults from Plugin
//    control.ftol                    =       *(double*)  mHost.ftol.getValueHandle();
//    control.xtol                    =       *(double*)  mHost.xtol.getValueHandle();
//    control.gtol                    =       *(double*)  mHost.gtol.getValueHandle();
//    control.epsilon                 =       *(double*)  mHost.epsilon.getValueHandle();
//    control.stepbound               =       *(double*)  mHost.stepbound.getValueHandle();
//    control.patience                =       *(int*)     mHost.patience.getValueHandle();


    //Setup data structures
    setup();

    //This is the library function doing the minimization..
//    lmmin(  mLMData.nrOfParameters,
//            mLMData.parameters,
//            mLMData.nrOfResiduePoints,
//			(const void*) &mHost,
//            evaluate,
//            &control,
//            &mHost.mLMStatus);


    //The user may have aborted the minization... check here..
    if(mHost.mTerminate)
    {
        //user did set the terminate flag to true.. discard any minimization data and get out of the
        //plugin execute code..
        Log(lInfo)<<"The Nelder-Mead minimization was terminated.. aborting";
        workerFinished();
        return;
    }

    //Post fitting data calculations
//    Log(lInfo)<<"==================== Fitting Result ================================";
//    Log(lInfo)<<"Nr of function evaluations: "  <<  mHost.mLMStatus.nfev;
//    Log(lInfo)<<"Status message: "              <<  lm_infmsg[mHost.mLMStatus.outcome];
//    Log(lInfo)<<"Minimized parameter values: ";
//
//    mHost.mStatusMessage.setValueFromString(lm_infmsg[mHost.mLMStatus.outcome]);
//
//    for (int i = 0; i < mLMData.nrOfParameters; ++i)
//    {
//        Log(lInfo)<<"Parameter "<<mLMData.parameterLabels[i]<<" = "<< mLMData.parameters[i];
//    }
//
//    Log(lInfo)<<"Norm:  "<<mHost.mLMStatus.fnorm;
//    postFittingWork();
    workerFinished();
}

void nmWorker::postFittingWork()
{
//    //Populate with data to report back
//    Properties& parsOut = mHost.mOutputParameterList.getValueReference();
//    parsOut.clear();
//    for (int i = 0; i < mLMData.nrOfParameters; ++i)
//    {
//        parsOut.add(new Property<double>(mLMData.parameters[i], mLMData.parameterLabels[i], ""), true);
//    }
//
//    Log(lError) <<"Parameters out.."<<parsOut;
//    //Set the norm property
//    mHost.mNorm.setValue(mHost.mLMStatus.fnorm);
//
//    //Create model and residuals data
//    createModelData(mHost.mModelData.getValuePointer());
//    createResidualsData(mHost.mResidualsData.getValuePointer());
//
//    //Truncate Norms property to actual number of iterations
//    TelluriumData tempData(mHost.mLMStatus.nfev, 1);
//    for(int r = 0; r < tempData.rSize(); r++)
//    {
//        tempData(r,0) = mHost.rNormsData(r, 0);
//    }
//    mHost.rNormsData = tempData;
//
//    //Calculate standardized residuals
//    TelluriumData& residuals = *(TelluriumData*) mHost.mResidualsData.getValueHandle();
//
//
//    //When there is a bad fit, residuals get really large and so
//    //several of the statistics below overflow
//
//    //Populate the standardized residuals
//    try
//    {
//        TelluriumData& stdRes = *(TelluriumData*) mHost.mStandardizedResiduals.getValueHandle();
//        stdRes = getStandardizedPopulations(residuals);
//
//        //Create a probability plot for the residuals
//        TelluriumData& probPlot = *(TelluriumData*) mHost.mNormalProbabilityOfResiduals.getValueHandle();
//        probPlot = getNormalProbabilityPlot(stdRes);
//
//        calculateChiSquare();
//        calculateHessian();
//        calculateCovariance();
//        calculateConfidenceLimits();
//    }
//    catch(...)
//    {
//        Log(lError) << "There was problems calculating fit statistics";
//    }
//
}

void nmWorker::calculateChiSquare()
{
    //Calculate ChiSquare(s)
    TelluriumData& modelData    = *(TelluriumData*) mHost.mModelData.getValuePointer();
    TelluriumData& obsData      = *(TelluriumData*) mHost.mExperimentalData.getValuePointer();
    
    Plugin* chi = mHost.mPM->getPlugin("tel_chisquare");

    if(!chi)
    {
        throw(Exception("Failed to get chisquare plugin in lmfit plugin"));
    }

    Property<TelluriumData>* para =  dynamic_cast<Property<TelluriumData>*>(chi->getProperty("ExperimentalData"));
    para->setValue(obsData);

    para =  dynamic_cast<Property<TelluriumData>*>(chi->getProperty("ModelData"));
    para->setValue(modelData);

    Property<int>* intPara =  dynamic_cast< Property<int>* >(chi->getProperty("NrOfModelParameters"));
//    intPara->setValue(mLMData.nrOfParameters);
//
//    //Calculate Chi square
//    chi->execute();
//
//    Property<double>* chiSquare =  dynamic_cast< Property<double>* >(chi->getProperty("ChiSquare"));
//    Property<double>* rChiSquare =  dynamic_cast< Property<double>* >(chi->getProperty("ReducedChiSquare"));
//
//    mHost.mChiSquare.setValue(chiSquare->getValue());
//    mHost.mReducedChiSquare.setValue(rChiSquare->getValue());
//
//    Log(lInfo)<<"Chi Square = "<<chiSquare->getValue();
//    Log(lInfo)<<"Reduced Chi Square = "<<rChiSquare->getValue();
}

double nmWorker::getChi(const Properties& parameters)
{
    Log(lDebug)<<"Getting chisquare using parameters: "<<parameters;
    //Reset RoadRunner
    reset(mRRI);

    for(int i = 0; i < parameters.count(); i++)
    {
        Property<double> *para = (Property<double>*) (parameters[i]);
        mRRI->setValue(para->getName(), para->getValue());
    }

    rr::SimulateOptions options;
//    options.start = mLMData.timeStart;
//    options.duration = mLMData.timeEnd - mLMData.timeStart;
//    options.steps = mLMData.nrOfTimePoints - 1;
//    options.flags = options.flags | rr::SimulateOptions::RESET_MODEL;
//
//    rr::RoadRunnerData *modelData = NULL;
//    if(mRRI->simulate(&options))
//    {
//        modelData = mRRI->getSimulationResult();
//    }
//
//    TelluriumData& obsData      = *(TelluriumData*) mHost.mExperimentalData.getValuePointer();
//    Plugin* chi                 = mHost.mPM->getPlugin("tel_chisquare");
//
//    Property<TelluriumData>* para =  dynamic_cast<Property<TelluriumData>*>(chi->getProperty("ExperimentalData"));
//    para->setValue(obsData);
//
//    para =  dynamic_cast<Property<TelluriumData>*>(chi->getProperty("ModelData"));
//    para->setValue(TelluriumData(*(modelData)));
//
//    Property<int>* intPara =  dynamic_cast< Property<int>* >(chi->getProperty("NrOfModelParameters"));
//    intPara->setValue(mLMData.nrOfParameters);
//
//    //Calculate Chi square
//    chi->execute();
//    Property<double>* chiSquare =  dynamic_cast< Property<double>* >(chi->getProperty("ChiSquare"));
//    return chiSquare->getValue();
}

void nmWorker::calculateHessian()
{
    double eta = 6.06e-6;
    int nrOfParameters = mHost.mOutputParameterList.getValueReference().count();

    Properties& ref = mHost.mOutputParameterList.getValueReference();

    Properties copy; //Gotta add a copy/assignemnt opertor to Properties..
    for(int i = 0; i < ref.count(); i++)
    {
        copy.add(ref[i]);
    }

    //We need to calculate ChiSquares for various perturbatin around a parameter value, in order to get the Hessian
    DoubleMatrix mat(nrOfParameters, nrOfParameters);

    for(int i = 0; i < nrOfParameters; i++)
    {
        for(int j = 0; j < nrOfParameters; j++)
        {
            if(i == j)//Diagonal elements
            {
                Property<double>* p = (Property<double>*) copy[i];
                double origValue = p->getValue();
                double hi = eta * fabs(origValue);

                p->setValue(origValue + hi);
                double t1 = getChi(copy);

                p->setValue(origValue - hi);
                double t2 = getChi(copy);

                p->setValue(origValue);
                double t3 = getChi(copy);
                mat(i,j) = (t1 + t2 - 2.0 * t3) / (hi*hi);
            }
            else //Off diagonal elements
            {
                Property<double>* pi = (Property<double>*) copy[i];
                double origValueI = pi->getValue();

                Property<double>* pj = (Property<double>*) copy[j];
                double origValueJ = pj->getValue();
                double hi = eta * fabs(origValueI);
                double hj = eta * fabs(origValueJ);

                //Term1
                pi->setValue(origValueI + hi);
                pj->setValue(origValueJ + hj);
                double t1 = getChi(copy);

                //Term2
                pj->setValue(origValueJ);
                double t2 = getChi(copy);

                //Term3
                pi->setValue(origValueI);
                pj->setValue(origValueJ + hj);
                double t3 = getChi(copy);

                //Term4
                pi->setValue(origValueI);
                pj->setValue(origValueJ);
                double t4 = getChi(copy);
                mat(i,j) = (t1 - t2 -t3 + t4 )/(hi*hj);

            }
            //Reset parameter values

        }
    }
    mHost.mHessian.setValue(mat);
}


void nmWorker::calculateCovariance()
{
    //Check if Hessain is invertible
    DoubleMatrix mat = mHost.mHessian.getValue();

    ls::ComplexMatrix temp(mat); //Get a complex matrix from a double one. Imag part is zero

    ls::ComplexMatrix Inv = GetInverse(temp);

    DoubleMatrix temp2(mat.RSize(), mat.CSize());
    temp2 = Inv;

    mHost.mCovarianceMatrix.setValue(temp2);
}

void nmWorker::calculateConfidenceLimits()
{
    Properties& parameters = mHost.mOutputParameterList.getValueReference();

    Properties& conf = mHost.mConfidenceLimits.getValueReference();
    conf.clear();

    DoubleMatrix mat = mHost.mCovarianceMatrix.getValue();
    double chiReduced = mHost.mReducedChiSquare.getValue();
//    for (int i = 0; i < mLMData.nrOfParameters; ++i)
//    {
//        double delta = 1.96*sqrt(mat(i,i) * chiReduced);
//        conf.add(new Property<double>(delta, mLMData.parameterLabels[i] + string("_confidence"), ""), true);
//    }
}

void nmWorker::workerStarted()
{
    mHost.mIsWorking = true;
    if(mHost.mWorkStartedEvent)
    {
        mHost.mWorkStartedEvent(mHost.mWorkStartedData1, mHost.mWorkStartedData2);
    }
}

void nmWorker::workerFinished()
{
    mHost.mIsWorking = false;//Set this flag before event so client can query plugin about termination
    if(mHost.mWorkFinishedEvent)
    {
        mHost.mWorkFinishedEvent(mHost.mWorkFinishedData1, mHost.mWorkFinishedData2);
    }
}

bool nmWorker::setup()
{
    StringList& species         = mHost.mExperimentalDataSelectionList.getValueReference();   //Model data selection..
//    mLMData.nrOfSpecies         = species.Count();
//    Properties parameters       = mHost.mInputParameterList.getValue();
//    mLMData.nrOfParameters      = parameters.count();
//    mLMData.parameters          = new double[mLMData.nrOfParameters];
//    mLMData.mLMPlugin           = static_cast<TELHandle> (&mHost);
//
//    //Setup initial parameter values
//    for(int i = 0; i < mLMData.nrOfParameters; i++)
//    {
//        Property<double> *par = (Property<double>*) parameters[i];
//        if(par)
//        {
//            mLMData.parameters[i] = par->getValue();
//        }
//        else
//        {
//            throw("Bad stuff..");
//        }
//    }
//
//    //Patience is max number of iterations
//    mHost.rNormsData.reSize(mHost.patience.getValue() * (mLMData.nrOfParameters + 1), 1);
//
//    TelluriumData& obsData             = (mHost.mExperimentalData.getValueReference());
//    mLMData.nrOfTimePoints              = obsData.rSize();
//    mLMData.timeStart                   = obsData.getTimeStart();
//    mLMData.timeEnd                     = obsData.getTimeEnd();
//    mLMData.nrOfResiduePoints           = mLMData.nrOfSpecies * mLMData.nrOfTimePoints;
//    mLMData.time                        = new double[mLMData.nrOfTimePoints];
//
//    mLMData.experimentalData            = new double*[mLMData.nrOfSpecies];
//
//    if(obsData.hasWeights())
//    {
//        mLMData.experimentalDataWeights = new double*[mLMData.nrOfSpecies];
//    }
//
//    mLMData.speciesLabels               = new char*[mLMData.nrOfSpecies];
//
//    //Each species data points and label
//    for (int i = 0; i < mLMData.nrOfSpecies; i++)
//    {
//        mLMData.experimentalData[i]     = new double[mLMData.nrOfTimePoints];
//        mLMData.speciesLabels[i]        = createText(species[i]);
//
//        if(obsData.hasWeights())
//        {
//            mLMData.experimentalDataWeights[i] = new double[mLMData.nrOfTimePoints];
//        }
//    }
//
//    //Populate Experimental Data
//    for (int i = 0; i < mLMData.nrOfSpecies; i++)
//    {
//        for(int timePoint = 0; timePoint < mLMData.nrOfTimePoints; timePoint++)
//        {
//            if(i == 0)
//            {
//                mLMData.time[timePoint] = obsData(timePoint, 0);
//            }
//            mLMData.experimentalData[i][timePoint] = obsData(timePoint, i + 1);
//        }
//    }
//
//    //Populate weights..
//    if(obsData.hasWeights())
//    {
//        for (int i = 0; i < mLMData.nrOfSpecies; i++)
//        {
//            for(int timePoint = 0; timePoint < mLMData.nrOfTimePoints; timePoint++)
//            {
//                mLMData.experimentalDataWeights[i][timePoint] = obsData.getWeight(timePoint, i + 1);
//            }
//        }
//    }
//
//    mLMData.parameterLabels           = new char*[mLMData.nrOfParameters];
//    for (int i = 0; i < mLMData.nrOfParameters; i++)
//    {
//        mLMData.parameterLabels[i]     = createText(parameters[i]->getName());
//    }
//
//    mLMData.rrHandle                = mRRI;
//    mRRI->setSelections(species);
//
//    mLMData.mProgressEvent               = mHost.mWorkProgressEvent;
//    mLMData.mProgressEventContextData    = mHost.mWorkProgressData1;
//
//    return true;
}

bool nmWorker::setupRoadRunner()
{
    if(mRRI)
    {
        delete mRRI;
    }

    mRRI = new RoadRunner;
    mRRI->load(mHost.mSBML.getValue());
    mRRI->setSelections(mHost.getExperimentalDataSelectionList());
    return true;
}

/* function evaluation, determination of residues */
void evaluate(const double *par,       //Property vector
              int           m_dat,      //Dimension of residue vector
              const void   *userData,  //Data structure
              double       *fvec,      //residue vector..
              int          *userBreak  //Non zero value means termination
)
{
//    const NelderMead *thePlugin = (const NelderMead*) userData;
//    NelderMead* plugin = const_cast<NelderMead*>(thePlugin);
//	const lmDataStructure* myData = &(thePlugin->mLMData);
//
//    //Check if user have asked for termination..
//    if(thePlugin->isBeingTerminated())
//    {
//        (*userBreak) = -1; //This signals lmfit algorithm to break
//        return;
//    }
//
//    //Reset RoadRunner
//    reset(myData->rrHandle);
//
//    for(int i = 0; i < myData->nrOfParameters; i++)
//    {
//        setValue(myData->rrHandle, myData->parameterLabels[i], par[i]);
//        Log(lDebug)<<myData->parameterLabels[i]<<" = "<<par[i]<<endl;
//    }
//
//    rrc::RRDataHandle rrData = NULL;
//    rrData = simulateEx(   myData->rrHandle,
//                                myData->timeStart,
//                                myData->timeEnd,
//                                myData->nrOfTimePoints);
//    if(!rrData)
//    {
//        stringstream msg;
//        msg << "NULL data returned from RoadRunner simulateEx() function.";
//        char* lastError = getLastError();
//
//        if(lastError)
//        {
//            msg << "\nLast error was: "<<lastError;
//        }
//
//        Log(lError)<<msg.str();
//        rrc::freeText(lastError);
//        return;
//    }
//
//    //Don't create RRC data, use rrData directly here
//    RRCDataPtr rrcData = createRRCData(rrData);
//    //calculate fvec for each specie
//    int count = 0;
//    for(int i = 0; i < myData->nrOfSpecies; i++)
//    {
//        fvec[count] = 0;
//        for(int j = 0; j < myData->nrOfTimePoints; j++ )
//        {
//            double modelValue;
//            if(!rrc::getRRCDataElement(rrcData, j, i, &modelValue))
//            {
//                throw("Bad stuff...") ;
//            }
//
//            if(!isNaN(myData->experimentalData[i][j]))
//            {
//                fvec[count] = myData->experimentalData[i][j] - modelValue;
//
//                if(myData->experimentalDataWeights != NULL)
//                {
//                    if(myData->experimentalDataWeights[i][j] != 0) //Cause the first column is time... :( loks ugly
//                    {
//                        double weight =  myData->experimentalDataWeights[i][j];
//                        fvec[count] = fvec[count] / weight;
//                    }
//                }
//            }
//            else
//            {
//                fvec[count] = 0;
//            }
//            count++;
//        }
//    }
//
//    freeRRCData(rrcData);
//
//    if(plugin->hasProgressEvent())
//    {
//        //Assign data relevant to the progress
//        double norm = lm_enorm(m_dat, fvec);
//        plugin->mNrOfIter.setValue(plugin->mNrOfIter.getValue() + 1);
//        plugin->mNorm.setValue(norm);
//
//        //Add norm to Norms property
//        plugin->rNormsData(plugin->mNrOfIter.getValue() -1, 0) = plugin->mNorm.getValue();
//
//        //Pass trough event data
//        pair<void*, void*> passTroughData = plugin->getWorkProgressData();
//        plugin->WorkProgressEvent(passTroughData.first, passTroughData.second);
//    }
}

void nmWorker::createModelData(TelluriumData* _data)
{
    TelluriumData& data = *(_data);
    //We now have the parameters
    StringList selList("time");
    selList.Append(mHost.mModelDataSelectionList.getValue());

//    data.reSize(mLMData.nrOfTimePoints, selList.Count());
//    mRRI->reset();
//    mRRI->setSelections(selList);
//
//    for(int i = 0; i < mLMData.nrOfParameters; i++)
//    {
//        mRRI->setValue(mLMData.parameterLabels[i], mLMData.parameters[i]);
//    }
//
//    rr::SimulateOptions options;
//    options.start = mLMData.timeStart;
//    options.duration = mLMData.timeEnd - mLMData.timeStart;
//    options.steps = mLMData.nrOfTimePoints - 1;
//    options.flags = options.flags | rr::SimulateOptions::RESET_MODEL;
//
//    if(mRRI->simulate(&options))
//    {
//        rr::RoadRunnerData rrData = *mRRI->getSimulationResult();
//        data = rrData;
//    }
}

void nmWorker::createResidualsData(TelluriumData* _data)
{
//    TelluriumData& resData = *(_data);
//    //We now have the parameters
//    TelluriumData& obsData = (mHost.mExperimentalData.getValueReference());
//    TelluriumData& modData = (mHost.mModelData.getValueReference());
//
//    resData.reSize(modData.rSize(), modData.cSize());
//
//    //setup coulumn names
//    resData.setColumnNames(modData.getColumnNames());
//
//    for(int sel = 0; sel < mLMData.nrOfSpecies + 1; sel++)    //selection 1 becuase of time column..
//    {
//        for(int i = 0; i < mLMData.nrOfTimePoints; i++)
//        {
//            if(sel == 0)
//            {
//                resData(i, sel) = modData(i, sel);    //Time
//            }
//            else
//            {
//                //The modData may contain data for other species than that was fitted..
//                //We need to find out what coulmn correspond to what..
//                string specie = obsData.getColumnName(sel);
//                int colNr = modData.getColumnIndex(specie);
//                if(colNr != -1)
//                {
//                    resData(i,sel) = obsData(i, sel) - modData(i, colNr);
//                }
//                else
//                {
//                    Log(lError)<<"Problem with column names when creating residual data!";
//                }
//            }
//        }
//    }
}
