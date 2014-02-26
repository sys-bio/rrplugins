#ifndef rrRandomH
#define rrRandomH
#include "third_party/mtrand.h"
#include "telMathExporter.h"
//---------------------------------------------------------------------------

namespace tlp
{

class MATH_DECLSPEC Random
{
    public:
                        Random();
        double          NextDouble() const;

    private:
        MTRand          mRand;        //Get a double in [0, 1)
};

}
#endif