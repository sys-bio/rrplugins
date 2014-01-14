#pragma hdrstop
#include "rrRoadRunnerData.h"
#include "rrLogger.h"
#include "add_noise_worker.h"
#include "rrUtils.h"
#include "noise.h"
#include "add_noise.h"
//---------------------------------------------------------------------------

namespace addNoise
{
using namespace rr;
AddNoiseWorker::AddNoiseWorker(AddNoise& host)
:
mTheHost(host)
{}

bool AddNoiseWorker::start(bool runInThread)
{
    if(runInThread)
    {
        if(mThread.isRunning())
        {
            Log(Logger::LOG_ERROR)<<"Tried to start a working thread!";
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

bool AddNoiseWorker::isRunning()
{
    return mThread.isRunning();
}

void AddNoiseWorker::run()
{
    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, mTheHost.mWorkStartedData2);
    }

    RoadRunnerData& data = (mTheHost.mData.getValueReference());
    Noise noise(0, mTheHost.mSigma.getValue());
    noise.randomize();

    for(int row = 0; row < data.rSize(); row++)
    {
        for(int col = 0; col < data.cSize() - 1; col++)
        {
            double yData = data(row, col + 1) + noise.getNoise();
            data(row, col + 1) = yData;
        }

        if(mTheHost.mWorkProgressEvent)
        {
            int progress = (int) (row * 100.0) /(data.rSize() -1.0);
            mTheHost.mProgress.setValue( progress );

            //The progress is communicated to the client as an INTEGER
            mTheHost.mWorkProgressEvent(mTheHost.mWorkProgressData1,  mTheHost.mWorkProgressData2);
        }
    }

    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent( mTheHost.mWorkFinishedData1, mTheHost.mWorkFinishedData2);
    }
}

}
