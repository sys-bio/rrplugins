#pragma hdrstop
#include <sstream>
#include "rr/rrLogger.h"
#include "telException.h"
#include "chisquare_doc.h"
#include "csChiSquare.h"
#include "telTelluriumData.h"
#include "telUtils.h"
//---------------------------------------------------------------------------

using namespace std;
using tlp::StringList;
ChiSquare::ChiSquare()
:
CPPPlugin(                      "ChiSquare", "Misc",       NULL, NULL),

//Properties.                   //value,                name,                                   hint,                                                           description, alias, readonly);
mExperimentalData(              TelluriumData(),        "ExperimentalData",                     "Data object holding Experimental data: Provided by client"),
mModelData(                     TelluriumData(),        "FittedData",                           "Data object holding model data: Handed to client"),

mChiSquare(                     0,                      "ChiSquare",                            "Chi-Square after fitting", "", "", true),
mReducedChiSquare(              0,                      "ReducedChiSquare",                     "Reduced Chi-Square after fitting", "", "", true),
mWorker(*this)
{
    mVersion = "0.8";

    //Add plugin properties to property container

    mProperties.add(&mExperimentalData);
    mProperties.add(&mModelData);

    mProperties.add(&mChiSquare);
    mProperties.add(&mReducedChiSquare);


    //Allocate model and Residuals data
    mModelData.setValue(new TelluriumData());

    mHint ="Create various statistics from experimental and modeled data input";
    mDescription="";
    //The function below assigns property descriptions
    assignPropertyDescriptions();
}

ChiSquare::~ChiSquare()
{}

bool ChiSquare::isWorking() const
{
    return mWorker.isRunning();
}

unsigned char* ChiSquare::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int ChiSquare::getPDFManualByteSize()
{
    return sizeofPDF;
}

string ChiSquare::getImplementationLanguage()
{
    return ::getImplementationLanguage();
}

bool ChiSquare::resetPlugin()
{
    if(mWorker.isRunning())
    {
        return false;
    }

    mTerminate = false;
    return true;
}


bool ChiSquare::execute(bool inThread)
{
    try
    {
        Log(lInfo)<<"Executing the ChiSquare plugin";
        mWorker.start(inThread);
        return true;
    }
    catch(const rr::Exception& ex)
    {
        Log(lError) << "There was a problem in the execute of the ChiSquare plugin: " << ex.getMessage();
        throw(ex);
    }
    catch(...)
    {
        Log(lError) << "There was an unknown problem in the execute of the ChiSquareFIT plugin.";
        throw("There was an unknown problem in the execute of the ChiSquareFIT plugin.");
    }
}

// Plugin factory function
ChiSquare* plugins_cc createPlugin()
{
    //allocate a new object and return it
    return new ChiSquare();
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

void ChiSquare::assignPropertyDescriptions()
{
    stringstream s;

s << "Experimental data contains the data to be used for fitting input.";
mExperimentalData.setDescription(s.str());
s.str("");

s << "Model data is calculated after the fitting algorithm finishes. It uses the obtained model parameters as input.";
mModelData.setDescription(s.str());
s.str("");


}

