#ifndef telLoadModelH
#define telLoadModelH
#include <string>
#include "rreThreadPool.h"
#include "rrRoadRunnerList.h"
#include "rreExporter.h"
//---------------------------------------------------------------------------

namespace rre
{
using std::string;
using namespace rr;

class RRE_DECLSPEC LoadModel : public ThreadPool
{
    public:
                    LoadModel(RoadRunnerList& rrs, const string& sbml, const int& nrThreads = 16, bool reCompile = true);
                   ~LoadModel();
};

}
#endif
