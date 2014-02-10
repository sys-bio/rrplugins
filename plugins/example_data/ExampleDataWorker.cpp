#pragma hdrstop
#include "telTelluriumData.h"
#include "rr/rrLogger.h"
#include "ExampleDataWorker.h"
#include "telUtils.h"
#include "ExampleData.h"
//---------------------------------------------------------------------------


ExampleDataWorker::ExampleDataWorker(ExampleData& host)
:
mTheHost(host)

{}

bool ExampleDataWorker::start(bool runInThread)
{
    if(runInThread)
    {
        if(mThread.isRunning())
        {
            Log(lError)<<"Tried to start a working thread!";
            return false;
        }

        //Run the worker in a thread
        mThread.start(*this);
    }
    else
    {
        run(); //Not running worker in a thread
    }
    return true;
}

bool ExampleDataWorker::isRunning() const
{
    return mThread.isRunning();
}

void ExampleDataWorker::run()
{
    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, mTheHost.mWorkStartedData2);
    }

    mTheHost.mWorkProgressEvent(mTheHost.mWorkProgressData1,  mTheHost.mWorkProgressData2);

    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent( mTheHost.mWorkFinishedData1, mTheHost.mWorkFinishedData2);
    }
}


