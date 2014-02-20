#ifndef rreLoadModelFromFileH
#define rreLoadModelFromFileH
#include "rreThreadPool.h"
#include "rrRoadRunnerList.h"
//---------------------------------------------------------------------------
namespace rre
{

class RRE_DECLSPEC LoadModelFromFile : public ThreadPool
{
    public:
                    LoadModelFromFile(RoadRunnerList& rrs, const string& modelFName, const int& nrThreads = 16);
                   ~LoadModelFromFile();
};

}
#endif
