#ifndef rrAutoWorkerH
#define rrAutoWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rr/rrRoadRunner.h"
#include "rr/rrOSSpecifics.h"
#include "telExporter.h"
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

using tlp::TelluriumData;

class AutoWorker : public Poco::Runnable
{
    public:
                                    AutoWorker(AutoPlugin& host);
                                   ~AutoWorker();
        bool                        start(bool runInThread = false);
        void                        run();
        bool                        isRunning() const;

    protected:
        Poco::Thread                mThread;
        AutoPlugin&                 mTheHost;
        rrauto::RRAuto&             mRRAuto;        //This class communicate with auto

        bool                        setup();
        TelluriumData              createModelData();
        TelluriumData              createResidualsData();
};
}
#endif
