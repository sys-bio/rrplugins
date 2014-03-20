#pragma hdrstop
#include "Poco/Path.h"
#include "Poco/File.h"
#include "telTelluriumData.h"
#include "telLogger.h"
#include "telAutoWorker.h"
#include "telAutoPlugin.h"
#include "telStringUtils.h"
#include "telUtils.h"
//---------------------------------------------------------------------------

using namespace tlp;
using namespace telauto;

AutoWorker::AutoWorker(AutoPlugin& host)
:
mTheHost(host),
mRRAuto(mTheHost.getRRAuto())
{}

AutoWorker::~AutoWorker()
{}

bool AutoWorker::isRunning() const
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

    if(!setupAuto())
    {
        Log(lError)<<"Failed to setup auto..";
        if(mTheHost.hasFinishedEvent())
        {
            pair<void*, void*> passTroughData = mTheHost.getWorkFinishedData();
            mTheHost.mWorkFinishedEvent(passTroughData.first, passTroughData.second);
        }
        return;
    }

    //==================== This is where we call auto
    mRRAuto.run();


    //Capture output data files
    string tempFolder;
    if(mTheHost.mTempFolder.getValue() == ".")
    {
        tempFolder = getCWD();
    }
    else
    {
        tempFolder = mTheHost.mTempFolder.getValue();
    }

    if(mTheHost.mCaptureOutputFiles.getValue() == true)
    {
        mTheHost.mFort2.setValue(getFileContent(joinPath(tempFolder, "fort.2")));
        mTheHost.mFort3.setValue(getFileContent(joinPath(tempFolder, "fort.3")));
        mTheHost.mFort8.setValue(getFileContent(joinPath(tempFolder, "fort.8")));
        mTheHost.mFort9.setValue(getFileContent(joinPath(tempFolder, "fort.9")));
    }

    //Fort 6 and 7 is always captured
    mTheHost.mFort6.setValue(getFileContent(joinPath(tempFolder, "fort.6")));
    //The bifurcation diagram is in fort.7, most important
    string fort7 = joinPath(tempFolder, "fort.7");
    if(!fileExists(fort7))
    {
        throw(Exception("Could not read auto data output file fort.7!"));
    }


    mTheHost.mFort7.setValue(getFileContent(fort7));

    //Cleanup after auto..
    if(mTheHost.mKeepTempFiles.getValue() == false)
    {
        StringList tempFiles("fort.2, fort.3, fort.8, fort.7, fort.9, fort.6");
        for(int i =0; i < tempFiles.count(); i++)
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

bool AutoWorker::setupAuto()
{
    //Transfer AUTO constants to AUTO interface
    mRRAuto.assignProperties(&(mTheHost.mProperties));

    if(mTheHost.mRR->isModelLoaded())
    {
        Log(lInfo)<<"Model already loaded..";
    }
    else
    {
        mTheHost.mRR->load(mTheHost.getSBML());
    }

    mRRAuto.selectParameter(mTheHost.mPrincipalContinuationParameter.getValue());

    if(mTheHost.mScanDirection.getValue() == "Positive")
    {
        mRRAuto.setScanDirection(sdPositive);
    }
    else
    {
        mRRAuto.setScanDirection(sdNegative);
    }

    string str = mRRAuto.getConstantsAsString();
    Log(lInfo)<<str;

}


