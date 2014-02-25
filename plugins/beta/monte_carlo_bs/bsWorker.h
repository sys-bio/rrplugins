#ifndef bsWorkerH
#define bsWorkerH
#include <vector>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "telPluginManager.h"
#include "telplugins_c_api.h"
#include "telTelluriumData.h"
//---------------------------------------------------------------------------

class MonteCarlo;

class bsWorker : public Poco::Runnable
{
    friend MonteCarlo;

    public:
                                    bsWorker(MonteCarlo& plugin);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;

    protected:
        Poco::Thread                mThread;
        MonteCarlo&                 mHostPlugin;

        bool                        setup();

        void                        workerStarted();
        void                        workerProgress();
        void                        workerFinished();

    private:
        const tlp::PluginManager*   mPM;

        tlpc::TELHandle             mLMPlugin;
        bool                        createInitialResiduals();
        tlp::TelluriumData          mInitialResiduals;
};

#endif
