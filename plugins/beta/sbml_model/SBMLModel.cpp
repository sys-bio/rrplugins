#pragma hdrstop
#include "SBMLModel.h"
#include "telException.h"
#include "telLogger.h"
#include "telUtils.h"
#include "telPluginManager.h"
#include "example_data_doc.h"

extern string theModel;
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
        mModel.setValue(theModel);
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

string  theModel =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>                                                                                     \
<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">                                             \
  <model metaid=\"_case00001\" id=\"case00001\" name=\"case00001\">                                                             \
    <listOfCompartments>                                                                                                        \
      <compartment id=\"compartment\" name=\"compartment\" size=\"1\" units=\"volume\"/>                                        \
    </listOfCompartments>                                                                                                       \
    <listOfSpecies>                                                                                                             \
      <species id=\"S1\" name=\"S1\" compartment=\"compartment\" initialAmount=\"0.00015\" substanceUnits=\"substance\"/>       \
      <species id=\"S2\" name=\"S2\" compartment=\"compartment\" initialAmount=\"0\" substanceUnits=\"substance\"/>             \
    </listOfSpecies>                                                                                                            \
    <listOfParameters>                                                                                                          \
      <parameter id=\"k1\" name=\"k1\" value=\"1\"/>                                                                            \
    </listOfParameters>                                                                                                         \
    <listOfReactions>                                                                                                           \
      <reaction id=\"reaction1\" name=\"reaction1\" reversible=\"false\" fast=\"false\">                                        \
        <listOfReactants>                                                                                                       \
          <speciesReference species=\"S1\"/>                                                                                    \
        </listOfReactants>                                                                                                      \
        <listOfProducts>                                                                                                        \
          <speciesReference species=\"S2\"/>                                                                                    \
        </listOfProducts>                                                                                                       \
        <kineticLaw>                                                                                                            \
          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">                                                                   \
            <apply>                                                                                                             \
              <times/>                                                                                                          \
              <ci> compartment </ci>                                                                                            \
              <ci> k1 </ci>                                                                                                     \
              <ci> S1 </ci>                                                                                                     \
            </apply>                                                                                                            \
          </math>                                                                                                               \
        </kineticLaw>                                                                                                           \
      </reaction>                                                                                                               \
    </listOfReactions>                                                                                                          \
  </model>                                                                                                                      \
</sbml>                                                                                                                         \
"
;

