#ifndef rrRoadRunnerListH
#define rrRoadRunnerListH
#include <vector>
#include <string>
#include "rreExporter.h"
#include "telConstants.h"
//#include "rrObject.h"
//---------------------------------------------------------------------------

namespace rre
{
using namespace rr;
using std::vector;
class RoadRunner;

class RRE_DECLSPEC RoadRunnerList //: public rrObject
{
    private:

    protected:
        vector<RoadRunner*>     mRRs;

    public:
                                RoadRunnerList(const int& nrOfRRs, const string& tempFolder = tlp::gEmptyString);
        virtual                ~RoadRunnerList();
        RoadRunner*             operator[](const int& index);
        unsigned int            count();

};

}
#endif
