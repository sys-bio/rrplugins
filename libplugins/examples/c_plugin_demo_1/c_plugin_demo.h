#ifndef c_plugin_demoH
#define c_plugin_demoH
#include "rrpExporter.h"
#include "rrplugins_types.h"
//-----------------------------------------------------------

//Global Plugin Data
RRPluginHandle      gPlugin;
RRPropertyHandle    gDemoProperty;
RRPropertiesHandle  gProperties;

//Each of these functions need to be present in order to load a plugin written in C
RR_PLUGIN_DECLSPEC const char*     call_conv getImplementationLanguage(void);
RR_PLUGIN_DECLSPEC const char*     call_conv getName(void);
RR_PLUGIN_DECLSPEC const char*     call_conv getCategory(void);
RR_PLUGIN_DECLSPEC bool            call_conv setupCPlugin(RRPluginHandle aPlugin);
RR_PLUGIN_DECLSPEC bool            call_conv execute(void* userData);
RR_PLUGIN_DECLSPEC bool            call_conv destroyPlugin(RRPluginHandle plugin);
RR_PLUGIN_DECLSPEC char*           call_conv getListOfCPluginPropertyNames(RRPluginHandle plugin);
RR_PLUGIN_DECLSPEC void*           call_conv getCPluginProperty(const char* name);

#endif



