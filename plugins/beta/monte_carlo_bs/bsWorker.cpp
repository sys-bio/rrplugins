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
//---------------------------------------------------------------------------

using namespace std;
using namespace tlp;

bsWorker::bsWorker(MonteCarlo& host)
:
mTheHost(host),
mRRI(NULL)
{

}

bool bsWorker::isRunning() const
{
    return mThread.isRunning();
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

    //The user may have aborted the minization... check here..
    if(mTheHost.mTerminate)
    {
        //user did set the terminate flag to true.. discard any minimization data and get out of the
        //plugin execute code..
        Log(lInfo)<<"The minimization was terminated.. aborting";
        workerFinished();
        return;
    }

    workerFinished();
}

void bsWorker::workerStarted()
{
    mTheHost.mIsWorking = true;
    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, mTheHost.mWorkStartedData2);
    }
}

void bsWorker::workerFinished()
{
    mTheHost.mIsWorking = false;//Set this flag before event so client can query plugin about termination
    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent(mTheHost.mWorkFinishedData1, mTheHost.mWorkFinishedData2);
    }
}

bool bsWorker::setup()
{
    return true;
}


