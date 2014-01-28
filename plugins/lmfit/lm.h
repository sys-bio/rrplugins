#ifndef lmH
#define lmH
#include <vector>
#include "telProperty.h"
#include "telCPPPlugin.h"
#include "rr/rrRoadRunner.h"
#include "lmWorker.h"
#include "lib/lmmin.h"
//---------------------------------------------------------------------------

namespace lmfit
{
using namespace tlp;
using rr::RoadRunner;
using std::string;

class LM : public CPPPlugin
{
    friend class lmWorker;

    public:
        Property<string>                        mSBML;                          //This is the model
        Property<TelluriumData>				    mExperimentalData;
        Property<TelluriumData>			        mModelData;


        Property<Properties>                    mInputParameterList;            //Parameters to fit
        Property<Properties>                    mOutputParameterList;           //Parameters that was fitted

        Property<tlp::StringList>               mExperimentalDataSelectionList; //Species selection list for observed data
        Property<tlp::StringList>               mModelDataSelectionList;        //Species selection list for observed data

        Property<int>                           mNrOfIter;                      //Part of minimization result

        //LMFIT Tuning parameters
        Property<double>                        ftol;                           /* relative error desired in the sum of squares. */
        Property<double>                        xtol;                           /* relative error between last two approximations. */
        Property<double>                        gtol;                           /* orthogonality desired between fvec and its derivs. */
        Property<double>                        epsilon;                        /* step used to calculate the jacobian. */
        Property<double>                        stepbound;                      /* initial bound to steps in the outer loop. */
        Property<int>                           patience;                       /* maximum number of iterations. */
        //Property<int>                           scale_diag;                   /* UNDOCUMENTED, TESTWISE automatical diag rescaling? */

        Property<double>                        mNorm;                          //Part of minimization result
        Property<TelluriumData>                 mNorms;                         //Norm values from the fitting
        TelluriumData&                          rNormsData;                     //Setup a reference to Norms Data

        Property<TelluriumData>			        mResidualsData;                 //Residuals from the fitting
        Property<TelluriumData>			        mStandardizedResiduals;         //Standardized Residuals from the fitting
        Property<TelluriumData>			        mNormalProbabilityOfResiduals;  //Normal probability of residuals
        Property<double>			            mChiSquare;                     //Normal probability of residuals
        Property<double>			            mReducedChiSquare;              //Normal probability of residuals

		//Utility functions for the thread
        string                                  getTempFolder();
        string                                  getSBML();

		lmDataStructure							&mLMData;        //LevenbergMarq.. data structure
    protected:
        //The worker is doing the work
        lmWorker                                mWorker;
        lm_status_struct                        mLMStatus;      //Check afterwards.

    public:
                                                LM();
                                               ~LM();

        bool                                    execute(bool inThread = false);
        string                                  getResult();
        bool                                    resetPlugin();
        string                                  getImplementationLanguage();
        string                                  getStatus();
        bool                                    isWorking() const;

        unsigned char*                          getManualAsPDF() const;
        unsigned int                            getPDFManualByteSize();
        tlp::StringList                         getExperimentalDataSelectionList();
        void                                    assignPropertyDescriptions();
};

extern "C"
{
RR_PLUGIN_DECLSPEC LM*         plugins_cc       createPlugin();
RR_PLUGIN_DECLSPEC const char* plugins_cc       getImplementationLanguage();
}
}
#endif
