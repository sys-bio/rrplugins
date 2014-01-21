#ifndef LMWorkerH
#define LMWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rr/rrRoadRunner.h"
#include "lmUtils.h"
//---------------------------------------------------------------------------

namespace lmfit
{

class LM;

using tlp::TelluriumData;

class LMWorker : public Poco::Runnable
{
    friend LM;

    protected:
        rr::RoadRunner             *mRRI;

        lmDataStructure             mLMData;        //LevenbergMarq.. data structure
        Poco::Thread                mThread;

        LM&                         mTheHost;
        bool                        setupRoadRunner();
        bool                        setup();
        void                        createModelData(TelluriumData* data);
        void                        createResidualsData(TelluriumData* data);
        void                        workerStarted();
        void                        workerFinished();
    public:
                                    LMWorker(LM& host);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;
};

}
#endif