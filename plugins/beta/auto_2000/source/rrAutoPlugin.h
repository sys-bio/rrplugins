#ifndef rrAutoPluginH
#define rrAutoPluginH
#include "telProperty.h"
#include "telCPPPlugin.h"
#include "telPluginManager.h"
#include "../rrAutoInterface/rrAutoData.h"
#include "../rrAutoInterface/rrRRAuto.h"
#include "rrAutoWorker.h"
#include "rrAutoPluginExporter.h"
//---------------------------------------------------------------------------

#if defined(__BORLANDC__)
    #define auto_cc __cdecl
#else
    #define auto_cc
#endif

using namespace rrauto;

class AutoPlugin : public CPPPlugin
{
    friend AutoWorker;
    public:
                                                AutoPlugin();
                                               ~AutoPlugin();
        //Data input
        void                                    setScanDirection(ScanDirection dir);
        bool                                    execute(bool inThread = false);
        string                                  getResult();
        string                                  getConstants();
        bool                                    resetPlugin();
        bool                                    setInputData(void* data);
        string                                  getStatus();
        bool                                    isWorking() const;
        RRAuto&                                 getRRAuto();

    protected:

        Property<string>                        mSBML;                  //This is the model
        Property<string>                        mTempFolder;
        Property<bool>                          mKeepTempFiles;
        Property<string>                        mScanDirection;         //How auto sweeps the parameter
        Property<string>                        mPrincipalContinuationParameter;
        Property<double>                        mPCPLowerBound;
        Property<double>                        mPCPUpperBound;
        Property<string>                        mBiFurcationDiagram;    //This is generated data

        //The interface to auto. Takes mAutoData as reference
        RRAuto                                  mRRAuto;

        string                                  getTempFolder();
        string                                  getSBML();

        //The worker
        AutoWorker                              mAutoWorker;

        //So make it a friend
        friend class AutoWorker;
};

extern "C"
{
RR_PLUGIN_DECLSPEC AutoPlugin* auto_cc       createPlugin();
RR_PLUGIN_DECLSPEC const char* auto_cc       getImplementationLanguage();
}




namespace tlp
{

template<>
inline string Property< rrauto::ScanDirection >::getValueAsString() const
{
    return mValue == rrauto::sdPositive ? "Positive" : "Negative";
}

template<>
inline void Property< rrauto::ScanDirection >::setValueFromString(const string& val)
{
    mValue = compareNoCase(val, "Positive") == 0 ? rrauto::sdPositive : rrauto::sdNegative;
}

template<>
inline void Property< rrauto::ScanDirection >::setValue(const rrauto::ScanDirection& val)
{
    mValue = (val);
}
}

#endif
