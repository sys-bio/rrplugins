#pragma hdrstop
#include "rr/rrLogger.h"
#include "SBMLModel.h"
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"
#include "example_data_doc.h"

//---------------------------------------------------------------------------
SBMLModel::SBMLModel(rr::RoadRunner* aRR, PluginEvent fn1, PluginEvent fn2, PluginEvent fn3)
:
CPPPlugin(  "SBMLModel",                 "Signal Processing",    aRR,    NULL),  //Construct Base

//Properties
mModel(              "",       "Model",       "A SBML model")
{
    mVersion = "1.0";

    //Setup the plugins properties
    mProperties.add(&mModel);

    mHint ="Get access to a example model and example TelluriumData, as strings";
    mDescription="The SBMLModel plugin exposes one property containing data, as a string, for an ExampleModel. \
The ExampleModel plugin was developed at the University of Washington by Totte Karlsson, 2012-2014.";

    //Load the model from file here..

}

SBMLModel::~SBMLModel()
{}

unsigned char* SBMLModel::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int SBMLModel::getPDFManualByteSize()
{
    return sizeofPDF;
}

bool SBMLModel::execute(bool inThread)
{
    Log(lDebug)<<"Executing the SBMLModel plugin by Totte Karlsson";
    return true;
}

// Plugin factory function
Plugin* plugins_cc createPlugin()
{
    //allocate a new object and return it
    return new SBMLModel;
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}





