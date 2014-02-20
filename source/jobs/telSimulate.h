#ifndef telSimulateH
#define telSimulateH
//---------------------------------------------------------------------------
#include "rrRoadRunnerList.h"
#include "rreThreadPool.h"

namespace rre
{
using namespace rr;
class RRE_DECLSPEC Simulate : public ThreadPool
{
    public:
                        Simulate(rre::RoadRunnerList& rrs, const int& nrThreads = 16);
                       ~Simulate();

};

}
#endif
