#ifndef bsWorkerH
#define bsWorkerH
#include <vector>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

#include "telPluginManager.h"
#include "telplugins_c_api.h"
#include "telTelluriumData.h"
#include "telRandom.h"
#include "telProperties.h"
//---------------------------------------------------------------------------

class MonteCarlo;
using tlp::TelluriumData;
using tlp::Properties;

class bsWorker : public Poco::Runnable
{
    friend MonteCarlo;

    public:
                                        bsWorker(MonteCarlo& plugin);
        void                            start(bool runInThread = true);
        void                            run();
        bool                            isRunning() const;

    protected:
        Poco::Thread                    mThread;
        MonteCarlo&                     mHostPlugin;

        bool                            setup();

        void                            workerStarted();
        void                            workerProgress();
        void                            workerFinished();


    private:
        const tlp::PluginManager*       mPM;
        tlp::Random                     mRandom;

        tlpc::TELHandle                 mLMPlugin;
        std::vector<double>             mResiduals;
        std::vector<TelluriumData*>     mMCDataSets;
        std::vector<Properties>         mMCParameters;

        void                            reset();

        bool                            createInitialResiduals();
        bool                            createMonteCarloDataSets();
        Properties                      getParameters(TelluriumData* data);

};

#endif
