#ifndef SBMLModelH
#define SBMLModelH
#include "telProperty.h"
#include "telCPPPlugin.h"
//---------------------------------------------------------------------------
using namespace tlp;

class SBMLModel : public CPPPlugin
{
    public:
                                    SBMLModel(RoadRunner* aRR = NULL, PluginEvent fn1 = NULL, PluginEvent fn2 = NULL, PluginEvent fn3 = NULL);
                                   ~SBMLModel();
        bool                        execute(bool);
        unsigned char*              getManualAsPDF() const;
        unsigned int                getPDFManualByteSize();

    private:
        Property<string>            mModel;
};

extern "C"
{
RR_PLUGIN_DECLSPEC Plugin*      plugins_cc createPlugin();
RR_PLUGIN_DECLSPEC const char*  plugins_cc getImplementationLanguage();
}
#endif
