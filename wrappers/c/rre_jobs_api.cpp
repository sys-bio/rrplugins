#pragma hdrstop
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "rr/rrRoadRunner.h"
#include "rr/rrException.h"
#include "rreLoadModel.h"
#include "rreLoadModelFromFile.h"
#include "rreSimulate.h"
#include "rreLoadModelThread.h"
#include "rreSimulateThread.h"
#include "telUtils.h"
#include "rr/rrLogger.h"
#include "telUtils.h"                   // Need to include this before the support header..
#include "telplugins_cpp_support.h"     // Need to include this before the support header..
#include "rre_jobs_api.h"
#include "rre_cpp_support.h"
#include "telplugins_cpp_support.h"
#include "rre_macros.h"
//---------------------------------------------------------------------------

namespace rre
{
using namespace std;
using namespace tlp;
using namespace tlpc;

RRJobHandle rre_cc loadSBMLFromFileJob(tlpc::TELHandle rrHandle, const char* fileName)
{
    start_try
        //Check if file exists first
        if(!fileExists(fileName))
        {
            stringstream msg;
            msg<<"The file "<<fileName<<" do not exist";
            rre::setError(msg.str());
            return NULL;
        }

        RoadRunner* rr = rre::castToRoadRunner(rrHandle);
        LoadModelThread* loadThread = new LoadModelThread(fileName);

        if(!loadThread)
        {
            rre::setError("Failed to create a LoadModel Thread");
        }
        loadThread->addJob(rr);
        loadThread->start();
        return loadThread;
    catch_ptr_macro
}

RRJobHandle rre_cc loadSBMLJob(tlpc::TELHandle rrHandle, const char* sbml)
{
    start_try
        RoadRunner* rr = rre::castToRoadRunner(rrHandle);
        LoadModelThread* loadThread = new LoadModelThread();
        loadThread->setSBML(sbml);

        if(!loadThread)
        {
            rre::setError("Failed to create a LoadModel Thread");
        }
        loadThread->addJob(rr);
        loadThread->start();
        return loadThread;
    catch_ptr_macro
}

RRJobHandle rre_cc loadSBMLFromFileJobEx(tlpc::TELHandle rrHandle, const char* fileName, bool recompile)
{
    start_try
        //Check if file exists first
        if(!fileExists(fileName))
        {
            stringstream msg;
            msg<<"The file "<<fileName<<" do not exist";
            rre::setError(msg.str());
            return NULL;
        }

        RoadRunner* rr = rre::castToRoadRunner(rrHandle);
        LoadModelThread* loadThread = new LoadModelThread(fileName, recompile);

        if(!loadThread)
        {
            rre::setError("Failed to create a LoadModel Thread");
        }

        loadThread->addJob(rr);
        loadThread->start();
        return loadThread;
    catch_ptr_macro
}

RRJobHandle rre_cc loadSBMLJobEx(tlpc::TELHandle rrHandle, const char* sbml, bool recompile)
{
    start_try

        RoadRunner* rr = rre::castToRoadRunner(rrHandle);
        LoadModelThread* loadThread = new LoadModelThread("", recompile);
        loadThread->setSBML(sbml);

        if(!loadThread)
        {
            rre::setError("Failed to create a LoadModel Thread");
        }

        loadThread->addJob(rr);
        loadThread->start();
        return loadThread;
    catch_ptr_macro
}

RRJobsHandle rre_cc loadSBMLFromFileJobs(RRInstanceListPtr _handles, const char* fileName, int nrOfThreads)
{
    start_try
        //Check if file exists first
        if(!fileExists(fileName))
        {
            stringstream msg;
            msg<<"The file "<<fileName<<" do not exist";
            rre::setError(msg.str());
            return NULL;
        }

        RoadRunnerList *rrs = getRRList(_handles);
        LoadModelFromFile* tp = new LoadModelFromFile(*rrs, fileName, nrOfThreads);

        if(!tp)
        {
            rre::setError("Failed to create a LoadModel Thread Pool");
        }
        return tp;
    catch_ptr_macro
}

RRJobsHandle rre_cc loadSBMLJobs(RRInstanceListPtr _handles, const char* sbml, int nrOfThreads)
{
    start_try
        RoadRunnerList *rrs = getRRList(_handles);
        LoadModel* tp = new LoadModel(*rrs, sbml, nrOfThreads);


        if(!tp)
        {
            rre::setError("Failed to create a LoadModel Thread Pool");
        }
        return tp;
    catch_ptr_macro
}

RRJobsHandle rre_cc loadSBMLJobsEx(RRInstanceListPtr _handles, const char* sbml, int nrOfThreads, bool reCompile)
{
    start_try
        RoadRunnerList *rrs = getRRList(_handles);
        LoadModel* tp = new LoadModel(*rrs, sbml, nrOfThreads, reCompile);


        if(!tp)
        {
            rre::setError("Failed to create a LoadModel Thread Pool");
        }
        return tp;
    catch_ptr_macro
}

bool rre_cc waitForJob(RRJobHandle handle)
{
    start_try
        RoadRunnerThread* aThread = (RoadRunnerThread*) handle;
        if(aThread)
        {
            aThread->waitForFinish();
            return true;
        }
        return false;
    catch_bool_macro
}

bool rre_cc waitForJobs(RRJobsHandle handle)
{
    start_try
        ThreadPool* aTP = (ThreadPool*) handle;
        if(aTP)
        {
            aTP->waitForFinish();
            return true;
        }
        return false;
    catch_bool_macro
}

bool rre_cc isJobFinished(RRJobHandle handle)
{
    start_try
        RoadRunnerThread* aT = (RoadRunnerThread*) handle;
        if(aT)
        {
            return ! aT->isActive();
        }
        return false;
    catch_bool_macro
}

bool rre_cc areJobsFinished(RRJobsHandle handle)
{
    start_try
        ThreadPool* aTP = (ThreadPool*) handle;
        if(aTP)
        {
            return ! aTP->isWorking();
        }
        return false;
    catch_bool_macro
}

int rre_cc getNumberOfRemainingJobs(RRJobHandle handle)
{
    start_try
        ThreadPool* aTP = (ThreadPool*) handle;
        if(aTP)
        {
            return aTP->getNumberOfRemainingJobs();
        }
        return -1;
    catch_int_macro
}

RRJobHandle rre_cc simulateJob(tlpc::TELHandle rrHandle)
{
    start_try
        RoadRunner *rr = rre::castToRoadRunner(rrHandle);
        SimulateThread *t = new SimulateThread(NULL, false);

        if(!t)
        {
            rre::setError("Failed to create a Simulate Thread Pool");
        }
        t->addJob(rr);
        t->start();
        return t;
    catch_ptr_macro
}

RRJobHandle rre_cc simulateJobEx(    tlpc::TELHandle rrHandle,
                                        double timeStart,
                                        double timeEnd,
                                        int numberOfPoints,
                                        callBackFunc f1,
                                        callBackFunc f2,
                                        void* userData)
{
    start_try
        RoadRunner *rr = rre::castToRoadRunner(rrHandle);
        SimulateThread *t = new SimulateThread(NULL, timeStart, timeEnd, numberOfPoints, f1, f2, userData, false);

        if(!t)
        {
            rre::setError("Failed to create a Simulate Thread Pool");
        }
        t->addJob(rr);
        t->start();
        return t;
    catch_ptr_macro
}

RRJobHandle rre_cc simulateJobs(RRInstanceListPtr _handles, int nrOfThreads)
{
    start_try
        RoadRunnerList *rrs = getRRList(_handles);
        Simulate* tp = new Simulate(*rrs, nrOfThreads);

        if(!tp)
        {
            rre::setError("Failed to create a Simulate Thread Pool");
        }
        return tp;
    catch_ptr_macro
}

RRJobHandle rre_cc simulateJobsEx(    RRInstanceListPtr _handles,
                                        int nrOfThreads,
                                        double timeStart,
                                        double timeEnd,
                                        int numPoints,
                                        callBackFunc fn1,
                                        callBackFunc fn2,
                                        void* userData)
{
    start_try
        RoadRunnerList *rrs = getRRList(_handles);

//        for(int i = 0; i < rrs->count(); i++)
//        {
//            (*rrs)[i]->setTimeStart(timeStart);
//            (*rrs)[i]->setTimeEnd(timeEnd);
//            (*rrs)[i]->setNumPoints(numPoints);
//        }

        Simulate* tp = new Simulate(*rrs, nrOfThreads);

        if(!tp)
        {
            rre::setError("Failed to create a Simulate Thread Pool");
        }
        return tp;
    catch_ptr_macro
}


bool rre_cc freeJob(RRJobHandle aJob, RRJobType jt)
{
    start_try
        switch(jt)
        {
            case jtLoadModel:
                delete (LoadModelThread*) aJob;
            break;

            case jtSimulate:
               delete (SimulateThread*) aJob;
            break;
            default:
            {
               Log(tlp::lError)<<"Failed to free job handle";
               return false;
            }
        }
        return true;
    catch_bool_macro
}

bool rre_cc freeJobs(RRJobsHandle handle)
{
    start_try
        ThreadPool* jobs = (ThreadPool*) handle;
        if(jobs)
        {
           delete jobs;
        }
        return true;
    catch_bool_macro
}

}
