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

int main()
{
    double scale = 1;
    Logger::setLevel(lDebug);
    Logger::enableFileLogging("Test.log");

    try
    {
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

//        TelluriumData model(        (TelluriumData*) test_model->getPropertyValueHandle("SimulatedData"));
//        TelluriumData experiment(   (TelluriumData*) test_model->getPropertyValueHandle("SimulatedDataWithNoise"));
//        model.write("r:\\modelData.dat");
//        experiment.write("r:\\expData.dat");

        Plugin* NMP = PM.getPlugin("Nelder-Mead");

        if(!NMP)
        {
            throw(Exception("NelderMead plugin is NULL.. Exiting"));
        }

        //Setup data structure
        NMP->setPropertyValue("SBML", test_model->getPropertyValueHandle("Model"));
        NMP->setPropertyValue("ExperimentalData", test_model->getPropertyValueHandle("SimulatedDataWithNoise"));

        //Setup parameters to fit
        Properties Parameters;
        Parameters.add(new Property<double>(12.3, "k1"));
        NMP->setPropertyValue("InputParameterList", &Parameters);
        NMP->setPropertyByString("ExperimentalDataSelectionList",   "S1,S2");
        NMP->setPropertyByString("FittedDataSelectionList",         "S1,S2");

        NMP->execute();

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



