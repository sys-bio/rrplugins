#pragma hdrstop
#include "rrRandom.h"
#include "third_party/mtrand.h"
//---------------------------------------------------------------------------

namespace tlp
{

Random::Random() {}

double Random::NextDouble() const
{
    return mRand();
}
}
