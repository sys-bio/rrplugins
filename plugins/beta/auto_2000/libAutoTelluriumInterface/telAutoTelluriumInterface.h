#ifndef telAutoTelluriumInterfaceH
#define telAutoTelluriumInterfaceH
#include "rr/rrRoadRunner.h"
#include "telAutoConstants.h"
#include "tai_exporter.h"
#include "telProperty.h"
#include "telLogger.h"
#include "telStringList.h"
#include "telProperties.h"
//---------------------------------------------------------------------------

#define autoCallConv __cdecl

//This class serves as a RoadRunner-Auto interface. It needs a roadrunner instance on creation
namespace telauto
{

using std::string;
using rr::RoadRunner;
using tlp::StringList;
using tlp::Properties;

class TA_DS AutoTellurimInterface
{
    public:
                                    AutoTellurimInterface(RoadRunner* rr);
                                   ~AutoTellurimInterface();
        string                      getTempFolder();
        bool                        setTempFolder(const string& fldr);
        bool                        setupUsingCurrentModel();
        string                      getConstantsAsString();
        void                        run();
        bool                        selectParameter(const string& para);
        bool                        setScanDirection(ScanDirection val);
        void                        assignRoadRunner(RoadRunner* rrInstance);
        void                        assignProperties(Properties* props);

    private:
        static string               mSelectedParameter;
        static StringList           mModelParameters;
        string                      mTempFolder;

        static RoadRunner*          mRR;            //Static so we can access this in autos callback
        static Properties*          mProperties;
        static AutoConstants        mAutoConstants;

        static int  autoCallConv    ModelInitializationCallback(long ndim, double t, double* u, double* par);
        static void autoCallConv    ModelFunctionCallback(const double* oVariables, const double* par, double* oResult);
};
}

namespace tlp
{
template<>
inline string getPropertyType<telauto::ScanDirection>(const telauto::ScanDirection& a)
{
    return "ScanDirection";
}
}

#endif
