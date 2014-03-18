#ifndef telAutoPluginH
#define telAutoPluginH
#include "telProperty.h"
#include "telCPPPlugin.h"
#include "telPluginManager.h"
#include "telAutoWorker.h"
#include "telAutoInputConstants.h"
#include "telAutoTelluriumInterface.h"
//---------------------------------------------------------------------------

#if defined(__BORLANDC__)
    #define auto_cc __cdecl
#else
    #define auto_cc
#endif

using telauto::AutoTellurimInterface;
using tlp::Property;
class AutoPlugin : public tlp::CPPPlugin
{
    friend AutoWorker;
    public:
                                                AutoPlugin();
                                               ~AutoPlugin();
        //Data input
        void                                    setScanDirection(telauto::ScanDirection dir);
        bool                                    execute(bool inThread = false);
        string                                  getResult();
        string                                  getConstants();
        bool                                    resetPlugin();
        bool                                    setInputData(void* data);
        string                                  getStatus();
        bool                                    isWorking() const;
        telauto::AutoTellurimInterface&         getRRAuto();

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
        AutoTellurimInterface                   mRRAuto;

        string                                  getTempFolder();
        string                                  getSBML();

        //The worker
        AutoWorker                              mAutoWorker;

        //So make it a friend
        friend class AutoWorker;
};

extern "C"
{
TLP_DS AutoPlugin* auto_cc       createPlugin();
TLP_DS const char* auto_cc       getImplementationLanguage();
}




namespace tlp
{

template<>
inline string Property< telauto::ScanDirection >::getValueAsString() const
{
    return mValue == telauto::sdPositive ? "Positive" : "Negative";
}

template<>
inline void Property< telauto::ScanDirection >::setValueFromString(const string& val)
{
    mValue = compareNoCase(val, "Positive") == 0 ? telauto::sdPositive : telauto::sdNegative;
}

template<>
inline void Property< telauto::ScanDirection >::setValue(const telauto::ScanDirection& val)
{
    mValue = (val);
}
}

#endif
