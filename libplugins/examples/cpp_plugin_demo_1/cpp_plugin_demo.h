#ifndef cpp_plugin_demoH
#define cpp_plugin_demoH
#include "../source/rrCPPPlugin.h"
#include "../source/rrProperty.h"
//---------------------------------------------------------------------------

namespace cpp_plugin_demo
{

class TestPlugin : public rrp::CPPPlugin
{
    private:
        rrp::Property<int>         mTestProperty;

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
RR_PLUGIN_DECLSPEC bool             plugins_cc    destroyPlugin(rrp::Plugin *plugin);

}

}    //Plugin Namespace




#endif
