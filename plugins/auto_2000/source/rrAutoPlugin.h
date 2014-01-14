#ifndef rrAutoPluginH
#define rrAutoPluginH
#include "rrProperty.h"
#include "rrCPPPlugin.h"
#include "rrPluginManager.h"
#include "../rrAutoInterface/rrAutoData.h"
#include "../rrAutoInterface/rrRRAuto.h"
#include "rrAutoWorker.h"
#include "rrAutoPluginExporter.h"
//---------------------------------------------------------------------------

namespace autoplugin
{
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
        void                                    setPrincipalContinuationParameter(const string& para);
        void                                    setPCPLowerBound(double lb);
        void                                    setPCPUpperBound(double ub);
        void                                    setSBML(const string& sbml);
        bool                                    execute(bool inThread = false);
        string                                  getResult();
        string                                  getConstants();
        bool                                    resetPlugin();
        bool                                    setInputData(void* data);
        string                                  getStatus();
        bool                                    isWorking();
        RRAuto&                                 getRRAuto();

    protected:

        Property<string>                        mTempFolder;
        Property<bool>                          mKeepTempFiles;
        Property<string>                        mSBML;                  //This is the model
        Property<string>                        mScanDirection;         //How auto sweeps the parameter
        Property<string>                        mPrincipalContinuationParameter;
        Property<double>                        mPCPLowerBound;
        Property<double>                        mPCPUpperBound;
        Property<string>                        mBiFurcationDiagram;    //This is generated data

        //This property is a container for parameters inside auto
        Property<Properties>                    mAutoParameters;

        RRAuto                                  mRRAuto;                //The interface to auto. Takes mAutoData as reference

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

}


namespace rrp
{

template<>
inline string Property< rrauto::ScanDirection >::getValueAsString() const
{
    return mValue == rrauto::sdPositive ? "Positive" : "Negative";
}

template<>
inline void Property< rrauto::ScanDirection >::setValueFromString(const string& val)
{
    mValue = rr::compareNoCase(val, "Positive") == 0 ? rrauto::sdPositive : rrauto::sdNegative;
}

template<>
inline void Property< rrauto::ScanDirection >::setValue(const rrauto::ScanDirection& val)
{
    mValue = (val);
}
}

#endif
