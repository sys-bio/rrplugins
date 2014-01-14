#ifndef rrAutoOutputParserH
#define rrAutoOutputParserH
#include <vector>
#include "rrCapability.h"
#include "rrParameter.h"
#include "rrCPPPlugin.h"
#include "rrRoadRunner.h"
#include "rrStringList.h"
#include "../rrAutoInterface/rrAutoData.h"
#include "../rrAutoInterface/rrRRAuto.h"
#include "rrAutoOutputParserWorker.h"
#include "rrAutoOutputParserExporter.h"
//---------------------------------------------------------------------------

namespace autoplugin
{

using namespace rrauto;

//If plugin is loaded by a program that is binary compatible witht he plugin, we could use class functions directly.
class AutoOutputParser : public CPPPlugin
{
    public:
                                                AutoOutputParser();
                                               ~AutoOutputParser();
        //Data input
        bool                                    setInputData(void* data);
        bool                                    execute(void* inputData = NULL, bool useThread = false);
        string                                  getResult();
        bool                                    resetPlugin();
        string                                  getStatus();
        bool                                    isWorking();

    protected:
        Capability                              mAutoOutputParser;
        Property<string>                       mBiFurcationDiagram;        //This is the input
        Property< rr::StringList >             mLabeledSolutionPoints;     //Part of output


        //The worker
        AutoOutputParserWorker                  mAutoOutputParserWorker;

        //So make it a friend
        friend class AutoOutputParserWorker;

};

extern "C"
{
RR_PLUGIN_DECLSPEC AutoOutputParser* plugins_cc     createPlugin(rr::RoadRunner* aRR, const PluginManager* rrp);
RR_PLUGIN_DECLSPEC const char* plugins_cc           getImplementationLanguage();
}

}

namespace rrp
{
template<>
inline std::string Property< rrauto::ScanDirection >::getType() const
{
    return "ScanDirection";
}

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
