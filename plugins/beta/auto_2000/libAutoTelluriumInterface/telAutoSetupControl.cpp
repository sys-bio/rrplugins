#pragma hdrstop
#include "telAutoSetupControl.h"
//---------------------------------------------------------------------------

namespace telauto
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
//    return mInputConstants.getConstantsAsString();
}
}
