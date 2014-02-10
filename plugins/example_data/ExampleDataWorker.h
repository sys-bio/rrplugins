#ifndef ExampleDataWorkerH
#define ExampleDataWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "telExporter.h"
#include "noise.h"
//---------------------------------------------------------------------------

class ExampleData;

class ExampleDataWorker : public Poco::Runnable
{
    protected:
        Poco::Thread            mThread;
        ExampleData&            mTheHost;

    public:
                                ExampleDataWorker(ExampleData& mTheHost);
        bool                    start(bool runInThread = true);
        void                    run();
        bool                    isRunning() const;
};


#endif
