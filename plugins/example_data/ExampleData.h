#ifndef ExampleDataH
#define ExampleDataH
#include "telProperty.h"
#include "telCPPPlugin.h"
#include "telTelluriumData.h"
#include "ExampleDataWorker.h"

//---------------------------------------------------------------------------
using namespace tlp;

class ExampleData : public CPPPlugin
{
    public:
        friend class ExampleDataWorker;
        enum NoiseType {ntGaussian = 0, ntPsychological, ntUndefined};

    private:
        Property<int>               mNoiseType;
        Property<double>            mSigma;
        Property<TelluriumData>     mData;
        Property<double>            mProgress;
        ExampleDataWorker           mExampleDataWorker;

    public:
                                    ExampleData(RoadRunner* aRR = NULL, PluginEvent fn1 = NULL, PluginEvent fn2 = NULL, PluginEvent fn3 = NULL);
                                   ~ExampleData();


        bool                        execute(bool inThread = false);
        bool                        isWorking() const; //Returns true as long the thread is active..
        unsigned char*              getManualAsPDF() const;
        unsigned int                getPDFManualByteSize();
};

extern "C"
{
RR_PLUGIN_DECLSPEC Plugin*      plugins_cc createPlugin();
RR_PLUGIN_DECLSPEC const char*  plugins_cc getImplementationLanguage();
}
#endif
