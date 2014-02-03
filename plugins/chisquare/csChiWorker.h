#ifndef csChiWorkerH
#define csChiWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "telTelluriumData.h"
//---------------------------------------------------------------------------

class ChiSquare;

using tlp::TelluriumData;

class ChiWorker : public Poco::Runnable
{
    friend ChiSquare;

    protected:
        Poco::Thread                mThread;

        ChiSquare&                       mTheHost;
        bool                        setupRoadRunner();
        bool                        setup();
        void                        createModelData(TelluriumData* data);
        void                        createResidualsData(TelluriumData* data);

        void                        workerStarted();
        void                        workerFinished();

    public:
                                    ChiWorker(ChiSquare& host);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;
};

#endif
