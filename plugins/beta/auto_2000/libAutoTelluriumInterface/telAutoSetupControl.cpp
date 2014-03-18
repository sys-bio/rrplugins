#pragma hdrstop
#include "telAutoSetupControl.h"
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
