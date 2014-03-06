#ifndef nmMinimizationDataH
#define nmMinimizationDataH
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"
#include "telProperties.h"
#include "telPlugin.h"

using rr::RoadRunner;
using tlp::TelluriumData;
using tlp::Properties;

class MinimizationData
{
    public:

        double              mEpsilon;
        double              mScale;
        TelluriumData       mExperimentalData;
        Properties          mParameters;        //Parameters to be minimized
        rr::RoadRunner      mRRI;
        TelluriumData       mNorms;

    public:
                            MinimizationData();
};

//---------------------------------------------------------------------------
#endif
