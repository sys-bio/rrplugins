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
    TelluriumData& expData      = mTheHost.mExperimentalData.getValueReference();
    TelluriumData& modelData    = mTheHost.mModelData.getValueReference();

    TelluriumData& chiSquare = mTheHost.mChiSquare.getValueReference();
    TelluriumData& redChiSquare = mTheHost.mReducedChiSquare.getValueReference();

    //If model data is an arrayed experiment, get chisquare experiment by experiment
    ArrayedParameter arrayedPara = modelData.getArrayedParameter();
    chiSquare.allocate(arrayedPara.getNumberOfIncrements() + 1, 2);     //Only supports one parameter at the moment
    redChiSquare.allocate(arrayedPara.getNumberOfIncrements() + 1, 2);  //Only supports one parameter at the moment

    chiSquare.setColumnNames(StringList("ExpNr, ChiSquare"));
    redChiSquare.setColumnNames(StringList("ExpNr, ReducedChiSquare"));
    for(int expNr = 1; expNr < arrayedPara.getNumberOfIncrements() + 2; expNr++)
    {
        TelluriumData mdlData = getDataSet(expNr, modelData);
        double chi = 0;

        //Get ChiSquare column by column and average them together
        int startCol = expData.isFirstColumnTime() ? 1 : 0;
        for(int n = startCol; n < expData.cSize(); n++)
        {
            vector<double> expDataN     = getValuesInColumn(n, expData);
            vector<double> variancesN   = getWeightValuesInColumn(n, expData);
            vector<double> modelDataN   = getValuesInColumn(n, mdlData);
            chi += getChiSquare(expDataN, modelDataN, variancesN);
        }

        int test = expData.isFirstColumnTime() ? 1 : 0;
        int nrOfCols = expData.cSize() -  test;
        int degreeOfFreedom = expData.rSize() * nrOfCols - mTheHost.mNrOfModelParameters.getValue();

        chiSquare(expNr -1, 0) = expNr;
        chiSquare(expNr -1, 1) = chi;

        redChiSquare(expNr -1, 0) = expNr;
        redChiSquare(expNr -1, 1) = chi/degreeOfFreedom;
    }

    Log(lInfo)<<"Chi Square = "<<chiSquare(0,1);
    Log(lInfo)<<"Reduced Chi Square = "<<redChiSquare(0,1);

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

