#ifndef bsWorkerH
#define bsWorkerH
#include <vector>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rr/rrRoadRunner.h"
#include "bsUtils.h"
#include "telTelluriumData.h"
#include "telProperties.h"
//---------------------------------------------------------------------------

namespace lmfit
{

using std::vector;
class MonteCarloBS;
using tlp::TelluriumData;
using tlp::Properties;

class bsWorker : public Poco::Runnable
{
    friend MonteCarloBS;

    protected:
        rr::RoadRunner             *mRRI;

        lmDataStructure             mLMData;        //LevenbergMarq.. data structure
        Poco::Thread                mThread;

        MonteCarloBS&                         mTheHost;
        bool                        setupRoadRunner();
        bool                        setup();
        void                        createModelData(TelluriumData* data);
        void                        createResidualsData(TelluriumData* data);
        void                        workerStarted();
        void                        workerFinished();
        void                        postFittingWork();
        void                        calculateChiSquare();
        void                        calculateHessian();
        void                        calculateCovariance();
        void                        calculateConfidenceLimits();
        double                      getChi(const Properties& parameters);

    public:
                                    bsWorker(MonteCarloBS& host);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;
};

}
#endif
