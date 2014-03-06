#ifndef TestModelH
#define TestModelH
#include "telProperty.h"
#include "telCPPPlugin.h"
#include "telTelluriumData.h"
//---------------------------------------------------------------------------
using namespace tlp;

class TestModel : public CPPPlugin
{
    public:
                                    TestModel(PluginManager* manager);
                                   ~TestModel();
        bool                        execute(bool);
        unsigned char*              getManualAsPDF() const;
        unsigned int                getPDFManualByteSize();

    private:
        const string                mModelFileName;
        Property<string>            mModel;
        Property<TelluriumData>     mSimulatedData;
        Property<TelluriumData>     mSimulatedDataWithNoise;
        Property<double>            mSigma;
        void                        addWeights();
};

extern "C"
{
RR_PLUGIN_DECLSPEC Plugin*      plugins_cc createPlugin(void* manager);
RR_PLUGIN_DECLSPEC const char*  plugins_cc getImplementationLanguage();
}
#endif
