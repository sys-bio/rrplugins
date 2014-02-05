#pragma hdrstop
#include "psParameterScanWorker.h"
#include "rr/rrLogger.h"
#include "telException.h"
#include "telTelluriumData.h"
#include "psParameterScan.h"
#include "telUtils.h"
#include "telMathUtils.h"
#include "telProperty.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace tlp;

ParameterScanWorker::ParameterScanWorker(ParameterScan& host)
:
mTheHost(host)
{}

bool ParameterScanWorker::isRunning() const
{
    return mThread.isRunning();
}

void ParameterScanWorker::start(bool runInThread)
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

void ParameterScanWorker::run()
{
    workerStarted();

    //The user may have aborted the minization... check here..
    if(mTheHost.isBeingTerminated())
    {
        //user did set the terminate flag to true.. discard any data and get out of the
        //plugin execute code..
        Log(lInfo)<<"The ParameterScanWorker was terminated.. aborting";
        workerFinished();
        return;
    }

    workerFinished();
}

void ParameterScanWorker::workerStarted()
{
    mTheHost.mIsWorking = true;
    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, mTheHost.mWorkStartedData2);
    }
}

void ParameterScanWorker::workerFinished()
{
    mTheHost.mIsWorking = false;//Set this flag before event so client can query plugin about termination
    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent(mTheHost.mWorkFinishedData1, mTheHost.mWorkFinishedData2);
    }
}

