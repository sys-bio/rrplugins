#ifndef SBMLModelH
#define SBMLModelH
#include "telProperty.h"
#include "telCPPPlugin.h"

//---------------------------------------------------------------------------
using namespace tlp;

class SBMLModel : public CPPPlugin
{
    public:
                                    SBMLModel(PluginManager* manager);
                                   ~SBMLModel();
        bool                        execute(bool);
        unsigned char*              getManualAsPDF() const;
        unsigned int                getPDFManualByteSize();

    private:
        const string                mModelFileName;
        Property<string>            mModel;
};

extern "C"
{
RR_PLUGIN_DECLSPEC Plugin*      plugins_cc createPlugin(void* manager);
RR_PLUGIN_DECLSPEC const char*  plugins_cc getImplementationLanguage();
}
#endif
