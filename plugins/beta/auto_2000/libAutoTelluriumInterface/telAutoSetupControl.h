#ifndef telAutoSetupControlH
#define telAutoSetupControlH
#include "telAutoInputConstants.h"
#include "tai_exporter.h"
//---------------------------------------------------------------------------

namespace telauto
{

class AutoTelluriumInterface;

class TA_DS SetupControl
{
    friend AutoTellurimInterface;

    public:
                                    SetupControl();
                                    /** This functions basically creates the auto input file fort.2
                                    */
        string                      getConstantsAsString();

    protected:
        InputConstants              mInputConstants;

        bool                        mCalculateSteadyState;
        bool                        mRunContinuation;
        bool                        mDirectionPositive;
};

}
#endif
