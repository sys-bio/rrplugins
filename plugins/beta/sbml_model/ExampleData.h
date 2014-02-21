#ifndef ExampleDataH
#define ExampleDataH
#include "telProperty.h"
#include "telCPPPlugin.h"
//---------------------------------------------------------------------------
using namespace tlp;

class SBMLModels : public CPPPlugin
{
    public:
                                    SBMLModels(RoadRunner* aRR = NULL, PluginEvent fn1 = NULL, PluginEvent fn2 = NULL, PluginEvent fn3 = NULL);
                                   ~SBMLModels();
        bool                        execute(bool);
        unsigned char*              getManualAsPDF() const;
        unsigned int                getPDFManualByteSize();

    private:
        Property<string>            mExampleModel;
};

extern "C"
{
RR_PLUGIN_DECLSPEC Plugin*      plugins_cc createPlugin();
RR_PLUGIN_DECLSPEC const char*  plugins_cc getImplementationLanguage();
}
#endif
