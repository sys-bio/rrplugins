#ifndef rrAutoWorkerH
#define rrAutoWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rrRoadRunner.h"
#include "rrOSSpecifics.h"
#include "rrpExporter.h"
#include "auto_utils.h"
//---------------------------------------------------------------------------

namespace rrauto
{
class RRAuto;
}

namespace autoplugin
{
typedef void (*ThreadCB)(void*, void*);

class AutoPlugin;

using rr::RoadRunnerData;

class AutoWorker : public Poco::Runnable
{
    public:
                                    AutoWorker(AutoPlugin& host);
                                   ~AutoWorker();
        bool                        start(bool runInThread = false);
        void                        run();
        bool                        isRunning();

    protected:
        Poco::Thread                mThread;
        AutoPlugin&                 mTheHost;
        rrauto::RRAuto&             mRRAuto;        //This class communicate with auto

        bool                        setup();
        RoadRunnerData              createModelData();
        RoadRunnerData              createResidualsData();
};
}
#endif
