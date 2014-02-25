#pragma hdrstop
#include "bsWorker.h"
#include "telLogger.h"
#include "rr/rrRoadRunnerOptions.h"
#include "telException.h"
#include "telTelluriumData.h"
#include "bsMonteCarlo.h"
#include "telUtils.h"
#include "telMathUtils.h"
#include "telProperty.h"
#include "telPluginManager.h"
#include "telPlugins_c_api.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace tlpc;

bsWorker::bsWorker(MonteCarlo& host)
:
mHostPlugin(host),
mPM(mHostPlugin.getPluginManager())
{
    if(!mPM)
    {
        throw(Exception("Monte carlo plugin need a plugin manager"));
    }
}

bool bsWorker::setup()
{
    mLMPlugin = mPM->getPlugin("tel_lm");

    if(!mLMPlugin)
    {
        throw(Exception("Monte Carlo plugin need the lmfit plugin"));
    }


    return true;
}

void bsWorker::start(bool runInThread)
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

void bsWorker::run()
{
    workerStarted();

    //The user may have aborted the monte carlo run. check if so here..
    if(mHostPlugin.mTerminate)
    {
        //user did set the terminate flag to true.. discard any minimization data and get out of the
        //plugin execute code..
        Log(lInfo)<<"The minimization was terminated.. aborting";
        workerFinished();
        return;
    }

    //Get to work..
    if(!setup())
    {
        Log(lError)<<"Failed setting up the Monte Carlo Bootstrap plugin aborting";
        return;
    }

    workerProgress();
    //Create MC data sets
    //First get initial residuals

    if(!createInitialResiduals())
    {
        Log(lError)<<"Failed creating initial residuals in Monte Carlo plugin..";
        return;
    }

    workerFinished();
}

bool bsWorker::createInitialResiduals()
{
    //Use the current minimization plugin to run one minimization and then use
    //the result to create residuals

    //Reset on each run
    resetPlugin(mLMPlugin);
    TELHandle paraHandle = getPluginProperty(mLMPlugin, "InputParameterList");

    if(!paraHandle)
    {
        throw(Exception("Failed to get Plugin Property in Monte Carlo plugin.."));
    }

    TELHandle parasHandle = getPropertyValueHandle(paraHandle);

    //Add input parameters, only the checked ones
    Properties* inputParameters = (Properties*) mHostPlugin.mInputParameterList.getValueHandle();
    int cnt = inputParameters->count();
    for(int i = 0; i < cnt ; i++)
    {
        PropertyBase* base = (*inputParameters)[i];
        Property<double>* para = (Property<double>*) (base); //->Items->Objects[i];

        //Do the creation of parameters earlier instead...
        TELHandle newPara = createProperty(para->getName().c_str(), "double", "", para->getValueHandle());
        addPropertyToList(parasHandle, newPara);
    }

    //Set input data to fit to
    TelluriumData* data = (TelluriumData*) mHostPlugin.mExperimentalData.getValueHandle();
    TELHandle experimentalData    = getPluginProperty(mLMPlugin, "ExperimentalData");
    setTelluriumDataProperty(experimentalData, data);

    //Add species to minimization data structure.. The species are defined in the input data
    StringList modelDataSelectionList = mHostPlugin.mModelDataSelectionList.getValue();
    paraHandle = getPluginProperty(mLMPlugin, "FittedDataSelectionList");
    setPropertyByString(paraHandle, modelDataSelectionList.AsString().c_str());

    TELHandle obsList = getPluginProperty(mLMPlugin, "ExperimentalDataSelectionList");
    StringList ExpDataSelectionList = mHostPlugin.mExperimentalDataSelectionList.getValue();

    setPropertyByString(obsList, ExpDataSelectionList.AsString().c_str());

    //Requirement => the modelDataSelection list must be equal or larger than the expSelectionlist
    if(ExpDataSelectionList.Count() > modelDataSelectionList.Count())
    {
        Log(lError)<<"The minimization engine requires the model selection list to be equal or larger than Experimental selection list";
        Log(lError)<<"Exiting Monte Carlo.";
        return false;
    }

    string strVal = mHostPlugin.mSBML.getValue();
    if(!setPluginProperty(mLMPlugin, "SBML", strVal.c_str()))
    {
        Log(lError)<<"Failed setting sbml";
        return false;
    }

//    assignOnStartedEvent(mLMPlugin,        fittingStartedCB,  this, NULL);
//    assignOnProgressEvent(mLMPlugin,       fittingProgressCB, this, NULL);
//    assignOnFinishedEvent(mLMPlugin,       fittingFinishedCB, this, NULL);

    executePluginEx(mLMPlugin, false);

    //We should now have residuals
    TelluriumData* residuals =   (TelluriumData*) getPluginPropertyValueHandle(mLMPlugin, "Residuals");

    Log(lDebug) <<"Logging residuals";
    Log(lDebug) << *(residuals);
    return true;
}

void bsWorker::workerStarted()
{
    mHostPlugin.mIsWorking = true;
    if(mHostPlugin.mWorkStartedEvent)
    {
        mHostPlugin.mWorkStartedEvent(mHostPlugin.mWorkStartedData1, mHostPlugin.mWorkStartedData2);
    }
}

void bsWorker::workerProgress()
{
    if(mHostPlugin.mWorkProgressEvent)
    {
        mHostPlugin.mWorkProgressEvent(mHostPlugin.mWorkProgressData1, mHostPlugin.mWorkProgressData2);
    }
}

void bsWorker::workerFinished()
{
    mHostPlugin.mIsWorking = false;//Set this flag before event so client can query plugin about termination
    if(mHostPlugin.mWorkFinishedEvent)
    {
        mHostPlugin.mWorkFinishedEvent(mHostPlugin.mWorkFinishedData1, mHostPlugin.mWorkFinishedData2);
    }
}

bool bsWorker::isRunning() const
{
    return mThread.isRunning();
}

