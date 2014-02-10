#pragma hdrstop
#include "rr/rrLogger.h"
#include "SBMLModels.h"
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"
#include "example_data_doc.h"

//---------------------------------------------------------------------------
SBMLModels::SBMLModels(rr::RoadRunner* aRR, PluginEvent fn1, PluginEvent fn2, PluginEvent fn3)
:
CPPPlugin(  "SBMLModels",                 "Signal Processing",    aRR,    NULL),  //Construct Base

//Properties
mExampleModel(              "",       "ExampleModel",       "An example model")
{
    mVersion = "1.0";

    //Setup the plugins properties
    mProperties.add(&mExampleModel);

    mHint ="Get access to a example model and example TelluriumData, as strings";
    mDescription="The SBMLModels plugin exposes one property containing data, as a string, for an ExampleModel. \
The ExampleModel plugin was developed at the University of Washington by Totte Karlsson, 2012-2014.";
}

SBMLModels::~SBMLModels()
{}

unsigned char* SBMLModels::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int SBMLModels::getPDFManualByteSize()
{
    return sizeofPDF;
}

bool SBMLModels::execute(bool inThread)
{
    Log(lDebug)<<"Executing the SBMLModels plugin by Totte Karlsson";
    return true;
}

// Plugin factory function
Plugin* plugins_cc createPlugin()
{
    //allocate a new object and return it
    return new SBMLModels;
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}





