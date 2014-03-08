#pragma hdrstop
#include <sstream>
#include "telLogger.h"
#include "telException.h"
#include "monte_carlo_bs_doc.h"
#include "bsMonteCarlo.h"
#include "telTelluriumData.h"
#include "telUtils.h"
//---------------------------------------------------------------------------

using namespace std;
using tlp::StringList;

MonteCarlo::MonteCarlo(PluginManager* manager)
:
CPPPlugin(                      "MonteCarlo-Bootstrap", "Fitting",       NULL, manager),

//Properties.                   //value,                name,                                   hint,                                                           description, alias, readonly);
mSBML(                          "<none>",               "SBML",                                 "SBML document as a string. Model to be used in the fitting"),
mExperimentalData(              TelluriumData(),        "ExperimentalData",                     "Data object holding Experimental data: Provided by client"),
mInputParameterList(            Properties(),           "InputParameterList",                   "List of parameters to fit"),
mMonteCarloParameters(          TelluriumData(),        "MonteCarloParameters",                 "Parameters obtained from a Monte Carlo session."),
mCurrentParameters(             Properties(),           "CurrentParameters",                    "List of parameters"),
mConfidenceLimits(              Properties(),           "ConfidenceLimits",                     "Confidence limits for each parameter"),
mExperimentalDataSelectionList( StringList(),           "ExperimentalDataSelectionList",        "Experimental data selection list"),
mModelDataSelectionList(        StringList(),           "FittedDataSelectionList",              "Fitted data selection list"),
mNrOfMCRuns(                    5,                      "NrOfMCRuns",                           "Number of Monte Carlo Data Sets"),
mMinimizerPlugin(               "Levenberg-Marquardt",  "MinimizerPlugin",                      "Minimizer used by the Monte Carlo Engine"),
mWorker(*this)
{
    mVersion = "0.8";

    //Add plugin properties to property container
    mProperties.add(&mSBML);
    mProperties.add(&mExperimentalData);
    mProperties.add(&mInputParameterList);
    mProperties.add(&mMonteCarloParameters);
    mProperties.add(&mCurrentParameters);
    mProperties.add(&mConfidenceLimits);
    mProperties.add(&mExperimentalDataSelectionList);
    mProperties.add(&mModelDataSelectionList);
    mProperties.add(&mNrOfMCRuns);
    mProperties.add(&mMinimizerPlugin);

    //Add the lmfit parameters
    mHint ="";
    mDescription="";
    //The function below assigns property descriptions
    assignPropertyDescriptions();
}

MonteCarlo::~MonteCarlo()
{}

bool MonteCarlo::isWorking() const
{
    return mWorker.isRunning();
}

unsigned char* MonteCarlo::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int MonteCarlo::getPDFManualByteSize()
{
    return sizeofPDF;
}

StringList MonteCarlo::getExperimentalDataSelectionList()
{
    return mExperimentalDataSelectionList.getValue();
}

string MonteCarlo::getStatus()
{
    stringstream msg;
    msg<<Plugin::getStatus();
    return msg.str();
}

string MonteCarlo::getImplementationLanguage()
{
    return ::getImplementationLanguage();
}

bool MonteCarlo::resetPlugin()
{
    if(mWorker.isRunning())
    {
        return false;
    }
    mWorker.reset();
    mTerminate = false;
    mInputParameterList.getValueReference().clear();

    mExperimentalDataSelectionList.getValueReference().clear();
    mModelDataSelectionList.getValueReference().clear();

    //Clear data
    mExperimentalData.clearValue();
    return true;
}

string MonteCarlo::getSBML()
{
    return mSBML.getValue();
}

string MonteCarlo::getResult()
{
    stringstream msg;
    Properties& conf = mConfidenceLimits;
    if(conf.count())
    {
        msg<<"Parameter confidence limits ========\n";
    }
    else
    {
        msg<<"No confidence limits to report ========";
    }

    for(int i = 0; i < conf.count(); i++)
    {
        Property<double>* confProp = dynamic_cast<Property<double>* > (conf[i]);
        msg<<confProp->getName()<<" => +/- "<<confProp->getValue()<<"\n";
    }
    return msg.str();
}

bool MonteCarlo::execute(bool inThread)
{
    try
    {
        Log(lInfo)<<"Executing the MonteCarlo plugin";
        mWorker.start(inThread);
        return true;
    }
    catch(const Exception& ex)
    {
        Log(lError) << "There was a problem in the execute of the MonteCarlo BootStrap plugin: " << ex.getMessage();
        throw(ex);
    }
    catch(...)
    {
        Log(lError) << "There was an unknown problem in the execute of the MonteCarlo BootStrap plugin.";
        throw("There was an unknown problem in the execute of the MonteCarlo BootStrap plugin.");
    }
}

// Plugin factory function
MonteCarlo* plugins_cc createPlugin(void* manager)
{
    //allocate a new object and return it
    return new MonteCarlo((PluginManager*) manager);
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

void MonteCarlo::assignPropertyDescriptions()
{
    stringstream s;
s << "The SBML property should be assigned the (XML) \
text that defines the SBML model that is used to fit parameters.";
mSBML.setDescription(s.str());
s.str("");

s << "Experimental data contains the data to be used for fitting input.";
mExperimentalData.setDescription(s.str());
s.str("");

s << "The input parameter list holds the parameters, and their initial values that are to be fitted, e.g. k1, k2. \
The input parameters are properties of the input SBML model";
mInputParameterList.setDescription(s.str());
s.str("");

s << "The confidence limits parameter list holds resulting confidence limits, as calculated using obtained Monte Carlo Parameters";
mConfidenceLimits.setDescription(s.str());
s.str("");

s << "The data input may contain multiple columns of data. The Experimental data selection list \
should contain the columns in the input data that is intended to be used in the fitting.";
mExperimentalDataSelectionList.setDescription(s.str());
s.str("");

s << "The model data selection list contains the selections for which model data will be genereated.  \
Model data can only be generated for selections present in the experimental data selectionlist.";
mModelDataSelectionList.setDescription(s.str());
s.str("");

s << "The number of iterations wil hold the number of iterations of the internal fitting routine.";
mNrOfMCRuns.setDescription(s.str());
s.str("");

}



