#ifndef lmWorkerH
#define lmWorkerH
#include <vector>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rr/rrRoadRunner.h"
#include "lmUtils.h"
#include "telTelluriumData.h"
//---------------------------------------------------------------------------

namespace lmfit
{

using std::vector;
class LM;

using tlp::TelluriumData;

class lmWorker : public Poco::Runnable
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
        vector<double>              getResidualsMeans(TelluriumData* residualsData);
        vector<double>              getResidualsStandardDeviations(vector<double> means, TelluriumData* residualsData);
        void                        workerStarted();
        void                        workerFinished();

    public:
                                    lmWorker(LM& host);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;
};

}
#endif
