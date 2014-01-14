#pragma hdrstop
#include "rrRRAutoSetupControl.h"
//---------------------------------------------------------------------------

namespace rrauto
{

SetupControl::SetupControl()
:
mCalculateSteadyState(true),
mRunContinuation(false),
mDirectionPositive(true)
{
}

string SetupControl::getConstantsAsString()
{
    return mInputConstants.getConstantsAsString();
}
}
