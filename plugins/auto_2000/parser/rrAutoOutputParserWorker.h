#ifndef rrAutoOutputParserWorkerH
#define rrAutoOutputParserWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rrRoadRunner.h"
#include "rrOSSpecifics.h"
#include "../rrAutoInterface/rrAutoData.h"
//---------------------------------------------------------------------------

namespace rrauto
{
class RRAuto;
}

namespace autoplugin
{
typedef void (callback_cc *ThreadCB)(void*);

class AutoOutputParser;

class AutoOutputParserWorker : public Poco::Runnable
{
    public:
                                    AutoOutputParserWorker(AutoOutputParser& host);
                                   ~AutoOutputParserWorker();
        void                        assignCallBacks(ThreadCB fn1, ThreadCB fn2, void* userData);
        bool                        start(bool runInThread = false);
        void                        run();
        bool                        isRunning();

    protected:
        Poco::Thread                mThread;

        //Callbacks
        ThreadCB                    threadEnterCB;
        ThreadCB                    threadExitCB;
        void*                       mUserData;       //Used for plugin callbacks..

        AutoOutputParser&           mTheHost;

        bool                        setup();
};
}
#endif
