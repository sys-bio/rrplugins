#ifndef rrRRAutoH
#define rrRRAutoH
#include "rrProperty.h"
#include "rrRoadRunner.h"
#include "rrLogger.h"
#include "rrRRAutoSetupControl.h"
#include "rrRRAutoExporter.h"
//---------------------------------------------------------------------------

#define autoCallConv __cdecl

//This class serves as a RoadRunner-Auto interface. It needs a roadrunner instance on creation
namespace rrauto
{

using std::string;
using rr::RoadRunner;
enum ScanDirection {sdPositive, sdNegative};

class RRA_DECLSPEC RRAuto
{
    public:
                                    RRAuto(RoadRunner* rr);
                                   ~RRAuto();
        string                      getTempFolder();
        bool                        setTempFolder(const string& fldr);
        bool                        setupUsingCurrentModel();
        string                      getConstantsAsString();
        bool                        run();
        bool                        reset();
        bool                        selectParameter(const string& para);
        bool                        setStartParameterValue(const double& val);
        bool                        setEndParameterValue(const double& val);
        bool                        setScanDirection(ScanDirection val);
        void                        assignRoadRunner(RoadRunner* rrInstance);

    private:
        static string               mSelectedParameter;
        string                      mTempFolder;

        static RoadRunner*          mRR;         //Static so we can access this in autos callback
        static SetupControl         mAutoSetup;  //Auto constants, parameters

        static int  autoCallConv    ModelInitializationCallback(long ndim, double t, double* u, double* par);
        static void autoCallConv    ModelFunctionCallback(const double* oVariables, const double* par, double* oResult);
};
}

namespace rrp
{
template<>
inline string getPropertyType<rrauto::ScanDirection>(const rrauto::ScanDirection& a)
{
    return "ScanDirection";
}
}

#endif
