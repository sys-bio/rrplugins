#pragma hdrstop
#include "nmObjectiveFunction.h"
#include "nmMinimizationData.h"
#include "telMathUtils.h"
//---------------------------------------------------------------------------

using namespace tlp;

double NelderMeadObjectiveFunction(double par[], const void* userData)
{
    MinimizationData&   myData  = *((MinimizationData*) userData);
    TelluriumData&      expData = myData.mExperimentalData;
    RoadRunner&         rr      = myData.mRRI;


    //Reset roadrunner
    rr.reset();

    //Get current parameter values
    int nrOfParameters = myData.mParameters.count();
    for(int i =0; i < nrOfParameters; i++)
    {
        PropertyBase* para = myData.mParameters[i];
        double parValue = par[i];
        para->setValue( &parValue  );
        if(!rr.setValue(para->getName(), * (double*) para->getValueHandle()))
        {
            throw(Exception("Failed setting value of parameter"));
        }

    }

    rr::SimulateOptions opt;
    opt.start       = expData.getTimeStart();
    opt.duration    = expData.getTimeEnd() - expData.getTimeStart();
    opt.steps       = expData.rSize() -1;
    TelluriumData simData(rr.simulate(&opt));

    //Calculate Norm

    double norm = getNorm(simData, expData);
//    myData.mNorms.a
    return norm;
}
