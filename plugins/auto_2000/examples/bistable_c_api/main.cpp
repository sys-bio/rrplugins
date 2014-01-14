#pragma hdrstop
#include <iostream>
#include <string>
#include "rrc_api.h"
#include "rrplugins_c_api.h"

using namespace std;
using namespace rrc;
using namespace rrp; //Plugin stuff
//using namespace autoplugin;

int main()
{
    string tempFolder("r:/temp");
    string sbmlFile("../models/bistable.xml");

    RRHandle  rri = NULL;
    try
    {
        string autoPluginName("rrp_auto2000");
        string autoOutputParserPluginName("rrp_AutoOutputParser");
        setLogLevel("LOG_DEBUG");

        cout<<"Current log level is: "<<getLogLevel();
        //A roadrunner object
        rri = createRRInstance();
        setTempFolder(rri, tempFolder.c_str());

        //A Plugin manager, using a roadrunner instance
        RRPluginManagerHandle pm = createPluginManager(rri);

        //Load auto plugin
        if(!loadPlugin(pm, autoPluginName.c_str()))
        {
            logMsg(clError, "Failed to load auto plugin");
            return 0;
        }

        //Get a plugin handle
        RRPluginHandle autoPlugin = getPlugin(pm, autoPluginName.c_str());
        if(!autoPlugin)
        {
            logMsg(clError, "Problem..");
            throw("AutoPlugin don't exist");
        }

        //A serious client would check if these calls are succesfull or not
        setPluginParameter(autoPlugin, "ScanDirection", "Negative");
        setPluginParameter(autoPlugin, "PrincipalContinuationParameter", "k3");
        setPluginParameter(autoPlugin, "PCPLowerBound", "0.2");
        setPluginParameter(autoPlugin, "PCPUpperBound", "1.2");

        //We can set the sbml parameter here or load into the roadrunner instance first
        //autoPlugin->setParameter("SBML", getFileContent(sbmlFile).c_str());

        //The load function does throw if file is not found.. is that what we want??
        if(!loadSBML(rri, sbmlFile.c_str()))
        {
            throw("Failed loading sbml model");
        }

        bool runInThread = true;
        if(!executePluginEx(autoPlugin, NULL, runInThread))
        {
            logMsg(clError, "Problem executing the Auto plugin");
            return 0;
        }

        if(runInThread)
        {
            while(isPluginWorking(autoPlugin))
            {
                logMsg(clInfo, "Plugin is working..");
            }
        }

        logMsg(clInfo, "Auto plugin is done.");
        RRParameterHandle biFurcationDiagram = getPluginParameter(autoPlugin, "BiFurcationDiagram", NULL);
        if(biFurcationDiagram)
        {
            string *temp =  (string*) getParameterValueAsPointer(biFurcationDiagram);
            logMsg(clInfo, temp->c_str());
        }

        //Parse auto output
        if(!loadPlugin(pm, autoOutputParserPluginName.c_str()))
        {
            logMsg(clError, "Failed to load auto output plugin");
            return 0;
        }

        //Get a plugin handle
        RRPluginHandle parseAutoOutput = getPlugin(pm, autoOutputParserPluginName.c_str());
        if(!parseAutoOutput)
        {
            logMsg(clError, "Problem..");
            throw("The parseAutoOutput Plugin don't exist");
        }

        executePluginEx(parseAutoOutput, getPluginParameter(autoPlugin, "BiFurcationDiagram", NULL), false);

        //Check if there were special solution points
        RRParameterHandle solutionPoints = getPluginParameter(parseAutoOutput, "LabeledSolutionPoints", NULL);

        char* msg = getParameterValueAsString(solutionPoints);

        logMsg(clInfo, msg);
        freeText(msg);
        unLoadPlugin(pm, parseAutoOutput);
        unLoadPlugin(pm, autoPlugin);
    }
    catch(...)
    {
        logMsg(clError, "Holy cow problem...!");
    }

    return 0;
}

#if defined(CG_UI)

#if defined(STATIC_APP)
    #pragma comment(lib, "roadrunner-static.lib")
    #pragma comment(lib, "rrplugins-static.lib")
    #pragma comment(lib, "roadrunner_c_api-static.lib")
    #pragma comment(lib, "rrplugins_c_api-static.lib")
    #pragma comment(lib, "libsbml-static.lib")
    #pragma comment(lib, "libxml2_xe.lib")
#else
    #pragma comment(lib, "roadrunner_c_api.lib")
    #pragma comment(lib, "rrplugins_c_api.lib")
#endif

#pragma comment(lib, "poco_foundation-static.lib")
//#pragma comment(lib, "cg32.lib")
#endif

