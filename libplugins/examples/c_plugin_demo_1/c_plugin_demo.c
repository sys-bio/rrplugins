#include <string.h>
#include "rrc_api.h"
#include "rrplugins_c_api.h"
#include "c_plugin_demo.h"

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
    setPropertyByString(gDemoProperty, "Intial Demo Property Value");

    //Add the property to the property container
    gProperties = createPropertyList();
    addPropertyToList(gProperties, gDemoProperty);

    return true;
}

bool call_conv execute()
{
    char *text1, *text2;
    RRHandle rrHandle;
    text1 = createTextMemory(4096);
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
    freeText(text1);
    return true;
}
