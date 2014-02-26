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
mModelData(                     TelluriumData(),        "FittedData",                           "Data object holding model data: Handed to client"),
mInputParameterList(            Properties(),           "InputParameterList",                   "List of parameters to fit"),
mOutputParameterList(           Properties(),           "OutputParameterList",                  "List of parameters that was fitted"),
mConfidenceLimits(              Properties(),           "ConfidenceLimits",                     "Confidence limits for each parameter"),
mExperimentalDataSelectionList( StringList(),           "ExperimentalDataSelectionList",        "Experimental data selection list"),
mModelDataSelectionList(        StringList(),           "FittedDataSelectionList",              "Fitted data selection list"),
mNrOfMCRuns(                    10,                     "NrOfMCRuns",                           "Number of Monte Carlo Data Sets"),
mWorker(*this)
{
    mVersion = "0.8";

    //Add plugin properties to property container
    mProperties.add(&mSBML);
    mProperties.add(&mExperimentalData);
    mProperties.add(&mModelData);
    mProperties.add(&mInputParameterList);
    mProperties.add(&mOutputParameterList);
    mProperties.add(&mConfidenceLimits);
    mProperties.add(&mExperimentalDataSelectionList);
    mProperties.add(&mModelDataSelectionList);
    mProperties.add(&mNrOfMCRuns);

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
    mOutputParameterList.getValueReference().clear();
    mExperimentalDataSelectionList.getValueReference().clear();
    mModelDataSelectionList.getValueReference().clear();

    //Clear data
    mExperimentalData.clearValue();
    mModelData.clearValue();

    return true;
}

string MonteCarlo::getSBML()
{
    return mSBML.getValue();
}

string MonteCarlo::getResult()
{
    stringstream msg;
    Properties& pars = mOutputParameterList.getValueReference();
    Properties& conf = mConfidenceLimits.getValueReference();

    for(int i = 0; i < pars.count(); i++)
    {
        Property<double>* prop = dynamic_cast< Property<double>* > (pars[i]);
        Property<double>* confProp = dynamic_cast<Property<double>* > (conf[i]);
        msg<<prop->getName()<<" = "<< prop->getValue() <<" +/- "<<confProp->getValue()<<"\n";
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

s << "The output parameter list holds the resulting fitted parameter(s)";
mOutputParameterList.setDescription(s.str());
s.str("");

s << "The confidence limits parameter list holds resulting confidence limits, as calculated from the Hessian";
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



