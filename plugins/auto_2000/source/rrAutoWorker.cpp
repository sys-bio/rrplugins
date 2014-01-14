#pragma hdrstop
#include "Poco/Path.h"
#include "Poco/File.h"
#include "rrRoadRunnerData.h"
#include "rrLogger.h"
#include "rrAutoWorker.h"
#include "rrAutoPlugin.h"
#include "rrStringUtils.h"
#include "rrUtils.h"
#include "rrc_api.h"
#include "rrc_utilities.h"
//---------------------------------------------------------------------------

namespace autoplugin
{

using namespace rr;

AutoWorker::AutoWorker(AutoPlugin& host)
:
mTheHost(host),
mRRAuto(mTheHost.getRRAuto())
{}

AutoWorker::~AutoWorker()
{}

bool AutoWorker::isRunning()
{
    return mThread.isRunning();
}

bool AutoWorker::start(bool runInThread)
{
    if(runInThread)
    {
        if(mThread.isRunning())
        {
            Log(lError)<<"Tried to start an already working thread!";
            return false;
        }

        mThread.start(*this);    //Will spawn the run function below in a thread
    }
    else
    {
        run();
    }
    return true;
}

void AutoWorker::run()
{
    if(mTheHost.hasStartedEvent())
    {
        pair<void*, void*> passTroughData = mTheHost.getWorkStartedData();
        mTheHost.mWorkStartedEvent(passTroughData.first, passTroughData.second);    //Tell anyone who wants to know
    }

    if(!setup())
    {
        Log(lError)<<"Failed to setup auto..";
        if(mTheHost.hasFinishedEvent())
        {
            pair<void*, void*> passTroughData = mTheHost.getWorkFinishedData();
            mTheHost.mWorkFinishedEvent(passTroughData.first, passTroughData.second);
        }
        return;
    }

    //Do the AUTO thing, pass data from the outside here..
    mRRAuto.selectParameter(mTheHost.mPrincipalContinuationParameter.getValue());
    double spvL = mTheHost.mPCPLowerBound.getValue();
    double spvU = mTheHost.mPCPUpperBound.getValue();

    mRRAuto.setStartParameterValue(spvL);
    mRRAuto.setEndParameterValue(spvU);
    mRRAuto.setScanDirection(sdNegative);

    ScanDirection sDirection = mTheHost.mScanDirection.getValue() == "Positive" ? sdPositive : sdNegative;

    string str = mRRAuto.getConstantsAsString();
    Log(lInfo)<<str;

    //==================== This is where auto is called
    if(!mRRAuto.run())
    {
        Log(lError)<<"There was a problem running auto";
    }
    //================================================

    //Parse output;
    string tempFolder;
    if(mTheHost.mTempFolder.getValue() == ".")
    {
        tempFolder = getCWD();
    }
    else
    {
        tempFolder = mTheHost.mTempFolder.getValue();
    }

    //The bifurcation diagram is in fort.7
    string fName = joinPath(tempFolder, "fort.7");
    if(!fileExists(fName))
    {
        throw(Exception("No Auto output data exists!"));
    }

    string f7(getFileContent(fName));

    //Pass the data to
    mTheHost.mBiFurcationDiagram.setValue(f7);

    //Cleanup after auto..

    if(mTheHost.mKeepTempFiles.getValue() == false)
    {
        StringList tempFiles("fort.2, fort.3, fort.8, fort.7, fort.9, stdout");
        for(int i =0; i < tempFiles.Count(); i++)
        {
            Poco::File tempFile(joinPath(tempFolder, tempFiles[i]));
            tempFile.remove();
        }
    }

    if(mTheHost.hasFinishedEvent())
    {
        pair<void*, void*> passTroughData = mTheHost.getWorkFinishedData();
        mTheHost.mWorkFinishedEvent(passTroughData.first, passTroughData.second);
    }
}

bool AutoWorker::setup()
{
    //Tempfolder setup
    string tFolder;
    if(mTheHost.mTempFolder.getValue() == ".")
    {
        tFolder = getCWD();
    }
    else
    {
        tFolder = mTheHost.mTempFolder.getValue();
    }

    mTheHost.mRR->setTempFileFolder(tFolder);
    mTheHost.mRRAuto.setTempFolder(tFolder);

    if(mTheHost.mRR->isModelLoaded())
    {
        Log(lInfo)<<"Model loaded by roadrunner outside of auto..";
        return true;
    }
    else
    {
        return mTheHost.mRR->load(mTheHost.getSBML());
    }
}

}


