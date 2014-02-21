#ifndef c_plugin_demoH
#define c_plugin_demoH
#include "telCoreExporter.h"
#include "telplugins_types.h"
//-----------------------------------------------------------
/*!
 \brief Global parameter holding last error, if any
*/
extern char*        gLastError;

//Global Plugin Data
TELHandle       gPlugin;
TELHandle       gDemoProperty;
TELHandle       gProperties;

//Each of these functions need to be present in order to load a plugin written in C
RR_PLUGIN_DECLSPEC const char*     call_conv getImplementationLanguage(void);
RR_PLUGIN_DECLSPEC const char*     call_conv getName(void);
RR_PLUGIN_DECLSPEC const char*     call_conv getCategory(void);
RR_PLUGIN_DECLSPEC bool            call_conv setupCPlugin(TELHandle aPlugin);
RR_PLUGIN_DECLSPEC bool            call_conv execute(bool inThread);
RR_PLUGIN_DECLSPEC bool            call_conv destroyPlugin(TELHandle plugin);
RR_PLUGIN_DECLSPEC char*           call_conv getListOfCPluginPropertyNames(TELHandle plugin);
RR_PLUGIN_DECLSPEC void*           call_conv getCPluginProperty(const char* name);

RR_PLUGIN_DECLSPEC char*           call_conv getCLastError();
#endif



