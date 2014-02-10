#pragma hdrstop
#include "SBMLModel.h"
#include "telException.h"
#include "rr/rrLogger.h"
#include "telUtils.h"
#include "telPluginManager.h"
#include "example_data_doc.h"

//---------------------------------------------------------------------------
SBMLModel::SBMLModel(PluginManager* manager)
:
CPPPlugin(  "SBMLModel",                 "Examples",    NULL,    manager),  //Construct Base

//Properties
mModel(              "",       "Model",       "A SBML model"),
mModelFileName("sbml_test_0001.xml")
{
    mVersion = "1.0";
    //Setup the plugins properties
    mProperties.add(&mModel);

    mHint ="Get access to an SBML model as a string";
    mDescription="The SBMLModel plugin exposes one property containing data, as a string, for an ExampleModel. \
The ExampleModel plugin was developed at the University of Washington by Totte Karlsson, 2012-2014.";

    //Load the model from file here..
    try
    {
        if(mPM)
        {
            //Get plugin folder
            string pluginFldr = mPM->getPluginDir();
            string cwd = getCWD();

            if(!fileExists(joinPath(pluginFldr,mModelFileName)))
            {
                throw(Exception("ModelFile do not exists!"));
            }

            string model = getFileContent(mModelFileName);
            mModel.setValue(model);
        }
    }
    catch(const exception& ex)
    {
        Log(lError)<<"There was a problem in the SBMLModel plugin: "<<ex.what();
    }
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
Plugin* plugins_cc createPlugin(void* manager)
{
    //allocate a new object and return it
    return new SBMLModel((PluginManager*) manager);
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}





