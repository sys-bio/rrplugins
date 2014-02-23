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

using std::vector;
class MonteCarlo;
using tlp::TelluriumData;
using tlp::Properties;

class bsWorker : public Poco::Runnable
{
    friend MonteCarlo;

    protected:
        rr::RoadRunner             *mRRI;

        Poco::Thread                mThread;

        MonteCarlo&                 mTheHost;
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
                                    bsWorker(MonteCarlo& host);
        void                        start(bool runInThread = true);
        void                        run();
        bool                        isRunning() const;
};


#endif
