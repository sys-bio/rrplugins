#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "telplugins_c_api.h"
#include "telplugins_types.h"
#include "c_plugin_demo.h"

char* gLastError = 0;
void setError(const char* err);

const char* call_conv getImplementationLanguage()
{
    return "C";
}

bool call_conv destroyPlugin(RRPluginHandle plugin)
{
    //Free any data that the plugin generated..
    freeProperty(gDemoProperty);
    freeProperties(gProperties);
    return true;
}

const char* call_conv getName()
{
    return "C Plugin Demo";
}

const char* call_conv getCategory()
{
    return "Demos";
}

char* call_conv getListOfCPluginPropertyNames(RRPluginHandle plugin)
{
    char* names = getNamesFromPropertyList(gProperties);
    return names;
}

void*  call_conv getCPluginProperty(const char* name)
{
    if(gPlugin)
    {
        return getProperty(gProperties, name);
    }
    else
    {
        return 0;
    }
}

bool call_conv setupCPlugin(RRPluginHandle aPlugin)
{
    gPlugin = aPlugin;
    gDemoProperty   = createProperty("Demo Property", "string", "Demo Hint", 0);
    if(!gDemoProperty)
    {
        //Failed to create property! Set last error and return false
        setError("Failed creating Property in c_plugin_demo");
        return false;
    }
    setPropertyByString(gDemoProperty, "Intial Demo Property Value");

    //Add the property to the property container
    gProperties = createPropertyList();
    addPropertyToList(gProperties, gDemoProperty);

    return true;
}

bool call_conv execute(bool inThread)
{
    char *text1, *text2;
    RRHandle rrHandle;
    text1       = (char*) malloc(4096 * sizeof(char));
    rrHandle    = createRRInstance();

    strcpy(text1, "CPP API Version: ");
    text2 = getCPPAPIVersion(rrHandle);
    if(text2)
    {
        strcat(text1, text2);
        setPropertyByString(gDemoProperty, text1);
    }
    else
    {
        return false;
    }

    //cleanup
    freeRRInstance(rrHandle);
    freeText(text2);
    free(text1);
    return true;
}

char* getCLastError()
{
    return gLastError;
}

void setError(const char* err)
{
    if(gLastError)
    {
        freeText(gLastError);
    }

    gLastError = createText(err);
}

