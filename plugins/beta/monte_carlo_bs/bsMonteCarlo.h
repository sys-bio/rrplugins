#ifndef bsMonteCarloH
#define bsMonteCarloH
#include <vector>
#include "telProperty.h"
#include "telCPPPlugin.h"
#include "telTelluriumData.h"
#include "bsWorker.h"

//---------------------------------------------------------------------------
using namespace tlp;
using std::string;

class MonteCarlo : public CPPPlugin
{
    friend class bsWorker;

    protected:
        Property<string>                        mSBML;                          //This is the model
        Property<TelluriumData>				    mExperimentalData;

        Property<Properties>                    mInputParameterList;            //Parameters to fit
        Property<Properties>                    mConfidenceLimits;              //Confidence limits for each parameter

        Property<tlp::StringList>               mExperimentalDataSelectionList; //Species selection list for observed data
        Property<tlp::StringList>               mModelDataSelectionList;        //Species selection list for observed data
        Property<int>                           mNrOfMCRuns;                    //Part of minimization result

		//Utility functions for the thread
        string                                  getTempFolder();
        string                                  getSBML();

    protected:

        //The worker is doing the work
        bsWorker                                mWorker;

    public:
                                                MonteCarlo(PluginManager* manager);
                                               ~MonteCarlo();

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
RR_PLUGIN_DECLSPEC MonteCarlo*    plugins_cc    createPlugin(void* manager);
RR_PLUGIN_DECLSPEC const char*    plugins_cc    getImplementationLanguage();
}




#endif
