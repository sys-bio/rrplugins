#pragma hdrstop
#include "nmObjectiveFunction.h"
#include "nmNelderMead.h"
#include "telMathUtils.h"
#include "telProperties.h"
//---------------------------------------------------------------------------

using namespace tlp;

double NelderMeadObjectiveFunction(double par[], const void* userData)
{
    NelderMead&         plugin      = *((NelderMead*) userData);
    TelluriumData&      expData     = plugin.mExperimentalData;
    RoadRunner*         rr          = plugin.getRoadRunner();

    if(!rr)
    {
        throw(Exception("RoadRunner is NULL in Nelder-Mead objective function"));
    }
    //Reset roadrunner
    rr->reset();

    //Get current parameter values
    Properties* inParas = (Properties*) plugin.mInputParameterList.getValueHandle();
    int nrOfParameters = inParas->count();

    for(int i = 0; i < nrOfParameters; i++)
    {
        PropertyBase* para = inParas->getPropertyAt(i);
//        para->setValue( &parValue  );
        if(!rr->setValue(para->getName(), par[i])) //* (double*) para->getValueHandle()))
        {
            throw(Exception("Failed setting value of RoadRunner parameter"));
        }
    }

    rr::SimulateOptions opt;
    opt.start       = expData.getTimeStart();
    opt.duration    = expData.getTimeEnd() - expData.getTimeStart();
    opt.steps       = expData.rSize() -1;

    //Simulate
    TelluriumData   simData(rr->simulate(&opt));

    StringList* species = (StringList*) plugin.mExperimentalDataSelectionList.getValueHandle();
    int nrOfSpecies = species->Count();

    //Calculate residuals
    vector<double> residuals(simData.rSize() * nrOfSpecies);

    int resIndex = 0;
    for(int specie = 0; specie < nrOfSpecies; specie++)
    {
        for(int timePoint = 0; timePoint < simData.rSize(); timePoint++)
        {
            residuals[resIndex] = expData(timePoint, specie + 1) - simData(timePoint, specie); //+1 because of time
            resIndex ++;
        }
    }

    //Calculate Norm
    double norm = getEuclideanNorm(residuals);

    //Call OnProgress
    if(plugin.hasProgressEvent())
    {
        //Assign data relevant to the progress
        plugin.mNrOfIter.setValue(plugin.mNrOfIter.getValue() + 1);
        plugin.mNorm.setValue(norm);

        //Add norm to Norms property
        plugin.rNormsData(plugin.mNrOfIter.getValue() -1, 0) = plugin.mNorm.getValue();

        //Pass trough event data
        pair<void*, void*> passTroughData = plugin.getWorkProgressData();
        plugin.WorkProgressEvent(passTroughData.first, passTroughData.second);
    }

    return norm;
}
