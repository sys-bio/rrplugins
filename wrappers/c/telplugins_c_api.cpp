#pragma hdrstop
#include <sstream>
#include "rr-libstruct/lsMatrix.h"
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"
#include "rr/rrLogger.h"
#include "telUtils.h"
#include "telPluginManager.h"
#include "telPlugin.h"
#include "telProperty.h"
#include "telStringUtils.h"
#include "tel_macros.h"
#include "telplugins_c_api.h"
#include "telplugins_cpp_support.h"

namespace tlpc
{
using namespace std;
using tlp::TelluriumData;
using namespace tlp;


RRPluginManagerHandle tlp_cc createPluginManager(const char* _pluginDir)
{
    start_try
        string pluginDir;
        if(!_pluginDir)
        {
            pluginDir = ".";
        }
        else
        {
            pluginDir = _pluginDir;
        }

        PluginManager* pm = new PluginManager(pluginDir);
        return pm;
    catch_ptr_macro
}


/**
 * free the plugin manager
 */
bool tlp_cc freePluginManager(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        delete pm;
        return true;
    catch_bool_macro
}

RRPluginHandle tlp_cc getFirstPlugin(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return pm->getFirstPlugin();
    catch_ptr_macro
}

RRPluginHandle tlp_cc getNextPlugin(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return pm->getNextPlugin();
    catch_ptr_macro
}

RRPluginHandle tlp_cc getPreviousPlugin(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return pm->getPreviousPlugin();
    catch_ptr_macro
}

RRPluginHandle tlp_cc getCurrentPlugin(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return pm->getCurrentPlugin();
    catch_ptr_macro
}

RRPluginHandle tlp_cc loadPlugin(RRPluginManagerHandle handle, const char* pluginName)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        if(pm->load(pluginName))
        {
            return pm->getPlugin(pluginName);
        }
        else
        {
            stringstream s;
            s << "Failed loading plugin: " + string(pluginName);
            s << "\n" <<pm->getLoadErrors();
            
            setError(s.str());
            return NULL;
        }
    catch_ptr_macro
}

bool tlp_cc loadPlugins(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        pm->load();
        return pm->hasLoadErrors() ? false : true;
    catch_bool_macro
}

char* tlp_cc getPluginLoadErrors(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return createText(pm->getLoadErrors());
    catch_ptr_macro
}

bool tlp_cc unLoadPlugins(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return pm->unload();
    catch_bool_macro
}

bool tlp_cc unLoadPlugin(RRPluginManagerHandle handle, RRPluginHandle plugin)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        Plugin* aPlugin = castToPlugin(plugin);
        if(pm->unload(aPlugin))
        {
            aPlugin = NULL;
            return true;
        }
        else
        {
            return false;
        }
    catch_bool_macro
}

int tlp_cc getNumberOfPlugins(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        return pm->getNumberOfPlugins();
    catch_int_macro
}

RRPluginHandle tlp_cc getPlugin(RRPluginManagerHandle handle, const char* pluginName)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        Plugin* aPlugin = pm->getPlugin(pluginName);
        return aPlugin;
    catch_ptr_macro
}

RRHandle tlp_cc getRRHandleFromPlugin(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->getRoadRunnerInstance();
    catch_ptr_macro
}

char* tlp_cc getPluginNames(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        StringList names = pm->getPluginNames();
        return createText(names.AsString());
    catch_ptr_macro
}

char* tlp_cc getPluginLibraryNames(RRPluginManagerHandle handle)
{
    start_try
        PluginManager *pm = castToPluginManager(handle);
        StringList names = pm->getPluginLibraryNames();
        return createText(names.AsString());
    catch_ptr_macro
}

char* tlp_cc getPluginName(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return createText(aPlugin->getName());
    catch_ptr_macro
}

char* tlp_cc getPluginCategory(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return createText(aPlugin->getCategory());
    catch_ptr_macro
}

char* tlp_cc getPluginDescription(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
    return createText(aPlugin->getDescription());
    catch_ptr_macro
}

char* tlp_cc getPluginHint(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
    return createText(aPlugin->getHint());
    catch_ptr_macro
}

RRPropertiesHandle tlp_cc getPluginProperties(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->getProperties();
    catch_ptr_macro
}

char* tlp_cc getListOfPluginPropertyNames(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);        
        return createText(aPlugin->getPropertyNames().AsString());
    catch_ptr_macro
}

RRPropertyHandle tlp_cc getPluginProperty(RRPluginHandle handle, const char* parameterName)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->getProperty(parameterName);
    catch_ptr_macro
}

bool tlp_cc setPluginProperty(RRPluginHandle handle, const char* parameterName, const char* value)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        PropertyBase* aProperty = (PropertyBase*) getPluginProperty(aPlugin, parameterName);
        return setPropertyByString(aProperty, value);
    catch_bool_macro
}

char* tlp_cc getPluginInfo(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return createText(aPlugin->getInfo());
    catch_ptr_macro
}

unsigned int tlp_cc getPluginManualNrOfBytes(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->getPDFManualByteSize();
    catch_ptr_macro
}

unsigned char* tlp_cc getPluginManualAsPDF(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->getManualAsPDF();
    catch_ptr_macro
}

char* tlp_cc getPluginStatus(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return createText(aPlugin->getStatus());
    catch_ptr_macro
}

bool tlp_cc assignRoadRunnerInstance(RRPluginHandle pHandle, RRHandle rrHandle)
{
    start_try
        Plugin* aPlugin = castToPlugin(pHandle);
        return (aPlugin) ? aPlugin->assignRoadRunnerInstance(static_cast<RoadRunner*>(rrHandle)) : false;
    catch_bool_macro
}

bool tlp_cc executePlugin(RRPluginHandle handle)
{
    return executePluginEx(handle, false);
}

bool tlp_cc executePluginEx(RRPluginHandle handle, bool inAThread)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return (aPlugin) ? aPlugin->execute(inAThread) : false;
    catch_bool_macro
}

bool tlp_cc assignOnStartedEvent(RRPluginHandle handle, tlpc::PluginEvent theCB, void* userData1, void* userData2)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return (aPlugin) ? aPlugin->assignOnStartedEvent(theCB, userData1, userData2) : false;
    catch_bool_macro
}

bool tlp_cc assignOnProgressEvent(RRPluginHandle handle, tlpc::PluginEvent theCB, void* userData1, void* userData2)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return (aPlugin) ? aPlugin->assignOnProgressEvent(theCB, userData1, userData2) : false;
    catch_bool_macro
}

bool tlp_cc assignOnFinishedEvent(RRPluginHandle handle, tlpc::PluginEvent theCB, void* userData1, void* userData2)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return (aPlugin) ? aPlugin->assignOnFinishedEvent(theCB, userData1, userData2) : false;
    catch_bool_macro
}

char* tlp_cc getPluginResult(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return createText(aPlugin->getResult());
    catch_ptr_macro
}

bool tlp_cc resetPlugin(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->resetPlugin();
    catch_bool_macro
}

bool tlp_cc isBeingTerminated(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->isBeingTerminated();
    catch_bool_macro
}

void tlp_cc terminateWork(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        aPlugin->terminate();
    catch_void_macro
}

bool tlp_cc wasTerminated(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->wasTerminated();
    catch_bool_macro
}

bool tlp_cc isPluginWorking(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return aPlugin->isWorking();
    catch_bool_macro
}

char* tlp_cc getLastError()
{   
    return gLastError; 
}

bool tlp_cc freeText(char* text)
{
    return tlp::freeText(text);
}

char* tlp_cc getPluginPropertiesAsXML(RRPluginHandle handle)
{
    start_try
        Plugin* aPlugin = castToPlugin(handle);
        return createText(aPlugin->getPluginPropertiesAsXML().c_str());
    catch_ptr_macro
}



}
