#pragma hdrstop
#include "rrRoadRunnerData.h"
#include "rrLogger.h"
#include "rrAutoOutputParserWorker.h"
#include "rrAutoOutputParser.h"
#include "lmfit/lmmin.h"
#include "rrStringUtils.h"
#include "rrUtils.h"
#include "rrc_api.h"
#include "rrc_utilities.h"
//---------------------------------------------------------------------------

namespace autoplugin
{

using namespace rr;

AutoOutputParserWorker::AutoOutputParserWorker(AutoOutputParser& host)
:
threadEnterCB(NULL),
threadExitCB(NULL),
mUserData(NULL),
mTheHost(host)
{}

AutoOutputParserWorker::~AutoOutputParserWorker()
{}

bool AutoOutputParserWorker::isRunning()
{
    return mThread.isRunning();
}

void AutoOutputParserWorker::assignCallBacks(ThreadCB fn1, ThreadCB fn2, void* userData)
{
    threadEnterCB     = fn1;
    threadExitCB      = fn2;
    mUserData         = userData;
}

bool AutoOutputParserWorker::start(bool runInThread)
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

void AutoOutputParserWorker::run()
{
    if(threadEnterCB)
    {
        threadEnterCB(mUserData);    //Tell anyone who wants to know
    }

    if(!setup())
    {
        Log(lError)<<"Failed to setup auto..";
        if(threadExitCB)
        {
            threadExitCB(mUserData);
        }
        return;
    }
    //Parse the bifurcation diagram and get the special points
    StringList diagram(splitString(mTheHost.mBiFurcationDiagram.getValue(),"\n"));
    StringList& labeledPoints =  *((StringList*) mTheHost.mLabeledSolutionPoints.getValueAsPointer());
    for(int i = 0; i < diagram.size(); i++)
    {
        string line = trim(diagram[i]);

        //Process lines starting with a '1'
        if(line.size() && line[0] == '1')
        {
            StringList dataRecord = splitString(line, " ");
            //look for special points, i.e. third record not being 0 or 4
            if(dataRecord.size() > 4)
            {
                if(     dataRecord[2] == "1" ||
                        dataRecord[2] == "2" ||
                        dataRecord[2] == "3" ||
                        dataRecord[2] == "5" ||
                        dataRecord[2] == "6" ||
                        dataRecord[2] == "7" ||
                        dataRecord[2] == "8" ||
                        dataRecord[2] == "-9"
                    )
                {
                 //We have a special point. Add the whole line
                 labeledPoints.add(line);
                }
            }
        }
    }

    if(threadExitCB)
    {
        threadExitCB(mUserData);
    }
}

bool AutoOutputParserWorker::setup()
{
    return true;
}

}


