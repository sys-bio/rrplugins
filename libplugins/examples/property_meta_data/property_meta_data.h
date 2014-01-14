#ifndef property_meta_dataH
#define property_meta_dataH
#include "../source/rrCPPPlugin.h"
#include "../source/rrProperty.h"
//---------------------------------------------------------------------------


class TestPlugin : public rrp::CPPPlugin
{
    private:
        rrp::Property<int>          mTestProperty;

    public:
                                    TestPlugin(int testParameter = 0);
                                   ~TestPlugin();

        bool                        execute(bool inThread = false);
};

extern "C"
{
RR_PLUGIN_DECLSPEC  const char*     plugins_cc    getImplementationLanguage();
RR_PLUGIN_DECLSPEC  TestPlugin*     plugins_cc    createPlugin(rr::RoadRunner* aRR);

// Plugin cleanup function
RR_PLUGIN_DECLSPEC bool             plugins_cc    destroyPlugin(rrp::Plugin *plugin);

}

#endif
