#include <stdio.h>
#include <math.h>
#include "rr/rrException.h"
#include "rr/rrRoadRunnerData.h"
#include "rr/rrRoadRunnerOptions.h"
#include "rr/rrRoadRunner.h"
#include "nmsimplex.h"
#include "telTelluriumData.h"
#include "telPluginManager.h"
#include "telLogger.h"
#include "telPlugin.h"
using namespace tlp;
using rr::RoadRunner;
class MinimizationData
{
    public:

        double              mEpsilon;
        double              mScale;

        TelluriumData       mExperimentalData;
        rr::RoadRunner      mRRI;
        TelluriumData       mChiSquares;
        Properties          mParameters;        //Parameters to be minimized
        Plugin*             mChiSquarePlugin;

    public:
                            MinimizationData();
};

MinimizationData::MinimizationData()
:
mEpsilon(1.e-18),
mScale(1)
{}

double objfun(double par[], const void* userData)
{
    MinimizationData&   myData  = *((MinimizationData*) userData);
    TelluriumData&      expData = myData.mExperimentalData;
    RoadRunner&         rr      = myData.mRRI;
    Plugin&             chi     = *(myData.mChiSquarePlugin);

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

    //Calculate Chi Square using the ChiSquare plugin
    chi.setPropertyValue("ModelData", &(simData));
    int nrOfParas = myData.mParameters.count();
    chi.setPropertyValue("NrOfModelParameters", &(nrOfParas));
    chi.execute(false);

    double chiSquare = * (double*) chi.getPropertyValueHandle("ChiSquare");
    return chiSquare;
}

int main()
{
    double scale = 1;
    Logger::setLevel(lDebug);
    Logger::enableFileLogging("Test.log");

    try
    {
        MinimizationData myData;

        PluginManager PM("..\\plugins");
        PM.load();

        Log(lInfo) << "The following plugins are loaded";
        Log(lInfo) << PM.getPluginNames();

        Plugin* test_model = PM.getPlugin("TestModel");
        if(!test_model)
        {
            throw(Exception("Test Model plugin is NULL!"));
        }
        test_model->execute();


        TelluriumData model(        (TelluriumData*) test_model->getPropertyValueHandle("SimulatedData"));
        TelluriumData experiment(   (TelluriumData*) test_model->getPropertyValueHandle("SimulatedDataWithNoise"));


        model.write("r:\\modelData.dat");
        experiment.write("r:\\expData.dat");

        Plugin* NMP = PM.getPlugin("Nelder_Mead");

         if(!NMP)
        {
            throw(Exception("NelderMead plugin is NULL.. Exiting"));
        }

        //Setup data structure
        NMP->setPropertyValue("SBML", test_model->getPropertyValueHandle("Model"));
        NMP->setPropertyValue("DataWithNoise", test_model->getPropertyValueHandle("DataWithNoise"));

        //Setup parameters to fit
        Properties Parameters;
        Parameters.add(new Property<double>(12.3, "k1"));
        NMP->setPropertyValue("InputParameterList", &Parameters);
        NMP->setProperty("ExperimentalDataSelectionList", "S1,S2");
        NMP->setProperty("FittedDataSelectionList", "S1,S2");


    }
    catch(const rr::Exception& e)
    {
        Log(lError) << "There was a problem: " << e.what();
    }
    catch(const tlp::Exception& e)
    {
        Log(lError) << "There was a problem: " << e.what();
    }


    return 0;
}


//void my_constraints(double x[], int n)
//{
//    // rate contstants must be positive
//    int i;
//    for (i=0; i<n; i++)
//    {
//        if (x[i] < 0)
//        {
//            x[i] = fabs(x[i]);
//        }
//    }
//}



