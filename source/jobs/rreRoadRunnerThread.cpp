#pragma hdrstop
#include "rreRoadRunnerThread.h"
#include "rr/rrLogger.h"
#include "telUtils.h"

namespace rre
{
using namespace Poco;
using namespace rr;
RoadRunnerThread::RoadRunnerThread() :
mIsTimeToDie(false),
mWasStarted(false),
mIsWorking(false)
{}

RoadRunnerThread::~RoadRunnerThread()
{}

bool RoadRunnerThread::wasStarted()
{
    return mWasStarted;
}

bool RoadRunnerThread::isWorking()
{
    return mIsWorking;
}

bool RoadRunnerThread::didFinish()
{
    return !isActive();
}

void RoadRunnerThread::setName(const string& name)
{
    mThread.setName(name);
}

string RoadRunnerThread::getName()
{
    return mThread.getName();
}

void RoadRunnerThread::exit()
{
    mIsTimeToDie = true;
    signalExit();
}

void RoadRunnerThread::start(RoadRunner* instance)
{
    if(instance)
    {
        addJob(instance);
    }

    mIsTimeToDie = false;

    if(mIsWorking)
    {
        Log(lError)<<"Tried to start a working thread!";
        return ;
    }

    mWasStarted = false;
    mIsWorking = false;

    mThread.start(*this);
}

void RoadRunnerThread::run()
{
    mWasStarted = true;
    worker();
}

void RoadRunnerThread::join()
{
    mThread.join();
}

bool RoadRunnerThread::isActive()
{
    return mThread.isRunning();
}

void RoadRunnerThread::waitForStart()
{

    while(mThread.isRunning() == false)
    {
        Poco::Thread::sleep(1);
    };
}

void RoadRunnerThread::waitForFinish()
{
    while(isActive() != false)
    {
        tlp::sleep(5);
    };
}

}