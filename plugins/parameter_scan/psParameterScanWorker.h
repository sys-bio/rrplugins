#ifndef psParameterScanWorkerH
#define psParameterScanWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "telTelluriumData.h"
//---------------------------------------------------------------------------

class ParameterScan;

using tlp::TelluriumData;

class ParameterScanWorker : public Poco::Runnable
{
    friend ParameterScan;

    protected:
        Poco::Thread                mThread;

        ParameterScan&                  mTheHost;

        void                        workerStarted();
        void                        workerFinished();

    public:
                                    ParameterScanWorker(ParameterScan& host);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;
};

#endif
