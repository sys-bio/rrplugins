#pragma hdrstop
#include <sstream>
#include "rr/rrLogger.h"
#include "telException.h"
#include "parameter_scan_doc.h"
#include "psParameterScan.h"
#include "telTelluriumData.h"
#include "telUtils.h"
//---------------------------------------------------------------------------

using namespace std;
using tlp::StringList;
ParameterScan::ParameterScan()
:
CPPPlugin(                      "ParameterScan", "Misc",       NULL, NULL),

//Properties.                   //value,                name,                                   hint,                                                           description, alias, readonly);
mOutputData(                    TelluriumData(),        "OutputData",                           "Data object holding Experimental data (input)"),
mParameters(                    ArrayedParameter() ,    "Parameter",                            "One Parameter (input)", "", "", true),
mWorker(*this)
{
    mVersion = "0.8";

    //Add plugin properties to property container
    mProperties.add(&mOutputData);
    mProperties.add(&mParameters);

    mHint = "Calculate data by incrementing one or more parameters.";
    mDescription="";
    //The function below assigns property descriptions
    assignPropertyDescriptions();
}

ParameterScan::~ParameterScan()
{}

bool ParameterScan::isWorking() const
{
    return mWorker.isRunning();
}

unsigned char* ParameterScan::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int ParameterScan::getPDFManualByteSize()
{
    return sizeofPDF;
}

string ParameterScan::getImplementationLanguage()
{
    return ::getImplementationLanguage();
}

bool ParameterScan::resetPlugin()
{
    if(mWorker.isRunning())
    {
        return false;
    }

    mTerminate = false;
    return true;
}

bool ParameterScan::execute(bool inThread)
{
    try
    {
        Log(lInfo)<<"Executing the ParameterScan plugin";
        mWorker.start(inThread);
        return true;
    }
    catch(const rr::Exception& ex)
    {
        Log(lError) << "There was a problem in the execute function of the ParameterScan plugin: " << ex.getMessage();
        throw(ex);
    }
    catch(...)
    {
        Log(lError) << "There was an unknown problem in the execute of the ParameterScan plugin.";
        throw("There was an unknown problem in the execute of the ParameterScan plugin.");
    }
}

// Plugin factory function
ParameterScan* plugins_cc createPlugin()
{
    //allocate a new object and return it
    return new ParameterScan();
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

void ParameterScan::assignPropertyDescriptions()
{
    stringstream s;

s << "Experimental data is used for input.";
mOutputData.setDescription(s.str());
s.str("");

s << "Property holding parameters to scan.";
mParameters.setDescription(s.str());
s.str("");

}

