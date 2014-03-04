#pragma hdrstop
#include <sstream>
#include "rr-libstruct/lsMatrix.h"
#include "rr/rrRoadRunner.h"
#include "telLogger.h"
#include "telTelluriumData.h"
#include "telUtils.h"
#include "telPluginManager.h"
#include "telPlugin.h"
#include "telProperty.h"
#include "telStringUtils.h"
#include "tel_macros.h"
#include "telplugins_c_api.h"
#include "telplugins_cpp_support.h"
#include "telOSSpecifics.h"
#include "telException.h"

namespace tlpc
{
using namespace std;
using rr::RoadRunner;
using tlp::TelluriumData;
using tlp::StringList;
using tlpc::createText;

TELHandle tlp_cc createPluginManager(const char* _pluginDir)
{
    start_try
        string pluginDir = (_pluginDir != NULL) ? string(_pluginDir) : string(".");

        PluginManager* pm = new PluginManager(pluginDir);
        gHM.registerHandle(pm, typeid(pm).name());

        return pm;
    catch_ptr_macro
}

/**
 * free the plugin manager
 */
bool tlp_cc freePluginManager(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        delete pm;
        return true;
    catch_bool_macro
}

TELHandle tlp_cc getFirstPlugin(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return pm->getFirstPlugin();
    catch_ptr_macro
}

TELHandle tlp_cc getNextPlugin(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return pm->getNextPlugin();
    catch_ptr_macro
}

TELHandle tlp_cc getPreviousPlugin(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return pm->getPreviousPlugin();
    catch_ptr_macro
}

TELHandle tlp_cc getCurrentPlugin(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return pm->getCurrentPlugin();
    catch_ptr_macro
}

TELHandle tlp_cc loadPlugin(TELHandle handle, const char* pluginName)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        if(pm->load(pluginName))
        {
            //Register plugins with Handle manager.
            Plugin* handle = pm->getPlugin(pluginName);
            return registerPlugin(handle);
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

bool tlp_cc loadPlugins(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        pm->load();

        //Register plugins with Handle manager.
        //We also need to register plugin attributes that may be
        //accessed trough the API
        Plugin* pl = pm->getFirstPlugin();
        while(pl)
        {
            registerPlugin(pl);
            pl = pm->getNextPlugin();
        };

        return pm->hasLoadErrors() ? false : true;
    catch_bool_macro
}

char* tlp_cc getPluginLoadErrors(TELHandle handle)
{

    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return createText(pm->getLoadErrors());
    catch_ptr_macro
}

bool tlp_cc unLoadPlugins(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return pm->unload();
    catch_bool_macro
}

bool tlp_cc unLoadPlugin(TELHandle handle, TELHandle plugin)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        Plugin* aPlugin = castHandle<Plugin>(plugin, __FUNC__);
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

int tlp_cc getNumberOfPlugins(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        return pm->getNumberOfPlugins();
    catch_int_macro
}

TELHandle tlp_cc getPlugin(TELHandle handle, const char* pluginName)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        Plugin* aPlugin = pm->getPlugin(pluginName);
        return aPlugin;
    catch_ptr_macro
}

TELHandle tlp_cc getRoadRunnerHandleFromPlugin(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->getRoadRunnerInstance();
    catch_ptr_macro
}

char* tlp_cc getPluginNames(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        StringList names = pm->getPluginNames();
        return createText(names.AsString());
    catch_ptr_macro
}

char* tlp_cc getPluginLibraryNames(TELHandle handle)
{
    start_try
        PluginManager *pm = castHandle<PluginManager>(handle, __FUNC__);
        StringList names = pm->getPluginLibraryNames();
        return createText(names.AsString());
    catch_ptr_macro
}

char* tlp_cc getPluginName(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getName());
    catch_ptr_macro
}

char* tlp_cc getPluginCategory(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getCategory());
    catch_ptr_macro
}

char* tlp_cc getPluginDescription(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getDescription());
    catch_ptr_macro
}

TLP_C_DS char* tlp_cc getPluginAuthor(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getAuthor());
    catch_ptr_macro
}

TLP_C_DS char* tlp_cc getPluginCopyright(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getCopyright());
    catch_ptr_macro
}

TLP_C_DS char* tlp_cc getPluginVersion(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getVersion());
    catch_ptr_macro
}


char* tlp_cc getPluginHint(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
    return createText(aPlugin->getHint());
    catch_ptr_macro
}

TELHandle tlp_cc getPluginProperties(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->getProperties();
    catch_ptr_macro
}

char* tlp_cc getListOfPluginPropertyNames(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getPropertyNames().AsString());
    catch_ptr_macro
}

TELHandle tlp_cc getPluginProperty(TELHandle handle, const char* parameterName)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->getProperty(parameterName);
    catch_ptr_macro
}

TELHandle tlp_cc getPluginPropertyValueHandle(TELHandle handle, const char* parameterName)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        PropertyBase* prop = aPlugin->getProperty(parameterName);
        if(prop)
        {
            return prop->getValueHandle();
        }
        else
        {
            return NULL;
        }
    catch_ptr_macro
}

char* tlp_cc getPluginPropertyValueAsString(TELHandle handle, const char* parameterName)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        PropertyBase* prop = aPlugin->getProperty(parameterName);
        if(prop)
        {
            return createText(prop->getValueAsString());
        }
        else
        {
            return NULL;
        }
    catch_ptr_macro
}

bool tlp_cc setPluginProperty(TELHandle handle, const char* parameterName, const char* value)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        PropertyBase* aProperty = (PropertyBase*) getPluginProperty(aPlugin, parameterName);
        if(!aProperty)
        {
            stringstream msg;
            msg <<"Failed locating property: "<<parameterName<<" in plugin: "<<aPlugin->getName()<<" and function: "<<__FUNC__;
            throw(tlp::Exception(msg.str()));
        }
        return setPropertyByString(aProperty, value);
    catch_bool_macro
}

char* tlp_cc getPluginInfo(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getInfo());
    catch_ptr_macro
}

unsigned int tlp_cc getPluginManualNrOfBytes(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->getPDFManualByteSize();
    catch_ptr_macro
}

unsigned char* tlp_cc getPluginManualAsPDF(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->getManualAsPDF();
    catch_ptr_macro
}

char* tlp_cc getPluginStatus(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getStatus());
    catch_ptr_macro
}

bool tlp_cc assignRoadRunnerInstance(TELHandle handle, TELHandle rrHandle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return (aPlugin) ? aPlugin->assignRoadRunnerInstance(static_cast<RoadRunner*>(rrHandle)) : false;
    catch_bool_macro
}

bool tlp_cc executePlugin(TELHandle handle)
{
    return executePluginEx(handle, false);
}

bool tlp_cc executePluginEx(TELHandle handle, bool inAThread)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return (aPlugin) ? aPlugin->execute(inAThread) : false;
    catch_bool_macro
}

bool tlp_cc assignOnStartedEvent(TELHandle handle, tlpc::PluginEvent theCB, void* userData1, void* userData2)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return (aPlugin) ? aPlugin->assignOnStartedEvent(theCB, userData1, userData2) : false;
    catch_bool_macro
}

bool tlp_cc assignOnProgressEvent(TELHandle handle, tlpc::PluginEvent theCB, void* userData1, void* userData2)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return (aPlugin) ? aPlugin->assignOnProgressEvent(theCB, userData1, userData2) : false;
    catch_bool_macro
}

bool tlp_cc assignOnFinishedEvent(TELHandle handle, tlpc::PluginEvent theCB, void* userData1, void* userData2)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return (aPlugin) ? aPlugin->assignOnFinishedEvent(theCB, userData1, userData2) : false;
    catch_bool_macro
}

char* tlp_cc getPluginResult(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getResult());
    catch_ptr_macro
}

bool tlp_cc resetPlugin(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->resetPlugin();
    catch_bool_macro
}

bool tlp_cc isBeingTerminated(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->isBeingTerminated();
    catch_bool_macro
}

void tlp_cc terminateWork(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        aPlugin->terminate();
    catch_void_macro
}

bool tlp_cc wasTerminated(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->wasTerminated();
    catch_bool_macro
}

bool tlp_cc isPluginWorking(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return aPlugin->isWorking();
    catch_bool_macro
}

char* tlp_cc getLastError()
{
    return gLastError;
}

char* tlp_cc getLastPluginAPIError()
{
    return gLastError;
}

bool tlp_cc freeText(char* text)
{
    return tlp::freeText(text);
}

char* tlp_cc getPluginPropertiesAsXML(TELHandle handle)
{
    start_try
        Plugin* aPlugin = castHandle<Plugin>(handle, __FUNC__);
        return createText(aPlugin->getPluginPropertiesAsXML().c_str());
    catch_ptr_macro
}

TELHandle tlp_cc registerHandle(TELHandle handle, char* name)
{
    return gHM.registerHandle(handle, name);
}

bool tlp_cc unRegisterHandle(TELHandle handle)
{
    return gHM.unRegisterHandle(handle);
}

}
