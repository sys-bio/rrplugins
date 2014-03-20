#pragma hdrstop
#include <iostream>
#include "telPluginManager.h"
#include "telException.h"
#include "telLogger.h"
#include "telPlugin.h"
#include "telUtils.h"
#include "telProperty.h"
#include "telAutoPlugin.h"
#include "telAutoTelluriumInterface.h"
#include "telAutoDataParser.h"

using namespace tlp;
using namespace std;
using namespace rr;

int main()
{
    string tempFolder("r:\\temp");
    string sbmlFile("../models/bistable.xml");
//    string sbmlFile("r:/models/BIOMD0000000203.xml");
	gLog.setLevel(lInfo);
    gLog.enableConsoleLogging();
    gLog.enableFileLogging(joinPath(tempFolder, "auto.log"));

    try
    {
        string pluginName("tel_auto2000");

        //A Plugin manager, using a roadrunner instance
        PluginManager pm("../plugins");

        //Load auto plugin
        if(!pm.load(pluginName))
        {
            Log(lError)<<"Failed to load plugin: "<<pluginName;
            return 0;
        }

        //Get a plugin handle and get some plugin info
        AutoPlugin* autoPlugin = (AutoPlugin*) pm.getPlugin(pluginName);
        if(!autoPlugin)
        {
            Log(lError)<<"Problem..";
            throw("AutoPlugin don't exist");
        }

        //A serious client would check if these calls are succesfull or not
        string sbml = getFileContent(sbmlFile);

        //Various plugin constants
        autoPlugin->setPropertyByString("SBML", sbml.c_str());
        autoPlugin->setPropertyByString("TempFolder", tempFolder.c_str());
        autoPlugin->setPropertyByString("KeepTempFiles", "true");

        //Specific auto parameters

        autoPlugin->setPropertyByString("ScanDirection", "Positive");
//        autoPlugin->setPropertyByString("ScanDirection", "Negative");
        autoPlugin->setPropertyByString("PrincipalContinuationParameter", "k3");
//        autoPlugin->setPropertyByString("PrincipalContinuationParameter", "A");
        autoPlugin->setPropertyByString("RL0", ".1");
        autoPlugin->setPropertyByString("RL1", "120");
        autoPlugin->setPropertyByString("NMX", "15000");

        if(!autoPlugin->execute(false))
        {
            Log(lError)<<"Problem executing the Auto plugin";
            return 0;
        }

        Log(lInfo)<<"Auto plugin is done.";
        Property<string>* biD = (Property<string>*) autoPlugin->getProperty("BiFurcationDiagram");
        Property<string>* biS = (Property<string>*) autoPlugin->getProperty("BiFurcationSummary");
        Log(lInfo)<<"BIFURCATION DIAGRAM\n"<< biD->getValue();
        Log(lInfo)<<"BIFURCATION SUMMARY\n"<< biS->getValue();

        //Parse the data
        AutoDataParser adp(biD->getValue());

        Log(lInfo) << "Number of data points: "         <<adp.getNumberOfDataPoints();
        Log(lInfo) << "Number of bifurcation points: "  <<adp.getNumberOfBifurcationPoints();
        StringList lines = adp.getDataFileHeader();
        Log(lInfo) << "Data header ===";
        for(int i = 0; i < lines.count(); i++)
        {
            Log(lInfo) << "line " << i << ": "<< lines[i];
        }

        Log(lInfo) <<"\n\n";

        lines = adp.getBiFurcationPoints();
        Log(lInfo) << "Labeled solutions header ===";
        for(int i = 0; i < lines.count(); i++)
        {
            Log(lInfo) << "line " << i << ": "<< lines[i];
        }

        Log(lInfo) << "As TelluriumData ===";

        TelluriumData data = adp.getSolutionData();
        Log(lInfo) << data;

        data.write("auto_data.dat");

        Log(lInfo)<<"\n\nAUTO 2000 is unloading...\n";
        //Check plugin data..
        pm.unload(autoPlugin);
    }
    catch(Exception& ex)
    {
        Log(lError)<<ex.getMessage();
    }
    catch(Poco::Exception& ex)
    {
        Log(lError)<<"Problem..."<<ex.message();
    }
    catch(exception& ex)
    {
        Log(lError)<<"Bad problem...!"<<ex.what();
    }

    catch(...)
    {
        Log(lError)<<"Bad problem...!";
    }

    pause(true);
    return 0;
}
