#pragma hdrstop
#include "csChiWorker.h"
#include "rr/rrLogger.h"
#include "telException.h"
#include "telTelluriumData.h"
#include "csChiSquare.h"
#include "telUtils.h"
#include "telMathUtils.h"
#include "telProperty.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace tlp;

ChiWorker::ChiWorker(ChiSquare& host)
:
mTheHost(host)
{}

bool ChiWorker::isRunning() const
{
    return mThread.isRunning();
}

void ChiWorker::start(bool runInThread)
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

void ChiWorker::run()
{
    workerStarted();

    //The user may have aborted the minization... check here..
    if(mTheHost.isBeingTerminated())
    {
        //user did set the terminate flag to true.. discard any data and get out of the
        //plugin execute code..
        Log(lInfo)<<"The ChiWorker was terminated.. aborting";
        workerFinished();
        return;
    }

    //Calculate ChiSquare
    TelluriumData& obsData      = *(TelluriumData*) mTheHost.mExperimentalData.getValuePointer();
    TelluriumData& modelData    = *(TelluriumData*) mTheHost.mModelData.getValuePointer();


    double chiSquare = 0;
    //Get ChiSquare specie by specie and average them together

    for(int n = obsData.isFirstColumnTime() ? 1 : 0; n < obsData.cSize(); n++)
    {
        vector<double> obsDataN     = getValuesInColumn(n, obsData);
        vector<double> modelDataN   = getValuesInColumn(n, modelData);


//        chiSquare += getChiSquare(obsDataN, modelDataN, variances);
    }
    //Divide chiSquare with number of species
    int test = obsData.isFirstColumnTime() ? 1 : 0;
    int nrOfSpecies = obsData.cSize() -  test;

//    int degreeOfFreedom = obsData.rSize() * nrOfSpecies - mChiSquareData.nrOfParameters;
//    mTheHost.mChiSquare.setValue(chiSquare);
//    mTheHost.mReducedChiSquare.setValue(chiSquare/degreeOfFreedom);

    Log(lInfo)<<"Chi Square = "<<chiSquare;

    //Post fitting data calculations
    workerFinished();
}

void ChiWorker::workerStarted()
{
    mTheHost.mIsWorking = true;
    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, mTheHost.mWorkStartedData2);
    }
}

void ChiWorker::workerFinished()
{
    mTheHost.mIsWorking = false;//Set this flag before event so client can query plugin about termination
    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent(mTheHost.mWorkFinishedData1, mTheHost.mWorkFinishedData2);
    }
}

