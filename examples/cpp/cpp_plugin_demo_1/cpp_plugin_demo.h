#ifndef cpp_plugin_demoH
#define cpp_plugin_demoH
#include "telCPPPlugin.h"
#include "telProperty.h"
//-------------------------------------------------------------------------

class TestPlugin : public tlp::CPPPlugin
{
    private:
        tlp::Property<int>         mTestProperty;

    public:
                                    TestPlugin();
                                   ~TestPlugin();
        
        bool                        execute(bool inThread);
};

extern "C"
{

RR_PLUGIN_DECLSPEC  const char*     plugins_cc    getImplementationLanguage();
RR_PLUGIN_DECLSPEC  TestPlugin*     plugins_cc    createPlugin();

// Plugin cleanup function
RR_PLUGIN_DECLSPEC bool             plugins_cc    destroyPlugin(tlp::Plugin *plugin);

}

#endif
