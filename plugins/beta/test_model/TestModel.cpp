#pragma hdrstop
#include "rr/rrRoadRunner.h"
#include "TestModel.h"
#include "telException.h"
#include "telLogger.h"
#include "telUtils.h"
#include "telPluginManager.h"
#include "test_model_doc.h"

extern string theModel;
//---------------------------------------------------------------------------
TestModel::TestModel(PluginManager* manager)
:
CPPPlugin(  "TestModel",                 "Examples",    NULL,    manager),  //Construct Base
//Properties
mModel(                         "",                     "Model",                    "A SBML model"),
mSimulatedData(                 TelluriumData(),        "SimulatedData",            "Simulated Data"),
mSimulatedDataWithNoise(        TelluriumData(),        "SimulatedDataWithNoise",   "Simulated Data With Noise"),
mSigma(                         3.e-6,                  "Sigma",                    "Sigma (<=> size of applied noise)"),
//Non properties
mModelFileName("sbml_test_0001.xml")
{
    mVersion = "1.0";
    //Setup the plugins properties
    mProperties.add(&mModel);
    mProperties.add(&mSimulatedData);
    mProperties.add(&mSimulatedDataWithNoise);

    mHint ="Get access to a SBML model, and simulated data using the model.";
    mDescription="The TestModel plugin exposes one property containing a simple SBML model as a string. \
The TestModel plugin was developed at the University of Washington by Totte Karlsson, 2012-2014.";

    //Load the model from file here..
    try
    {
        mModel.setValue(theModel);
    }
    catch(const exception& ex)
    {
        Log(lError)<<"There was a problem in the TestModel plugin: "<<ex.what();
    }
}

TestModel::~TestModel()
{}

unsigned char* TestModel::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int TestModel::getPDFManualByteSize()
{
    return sizeofPDF;
}

bool TestModel::execute(bool inThread)
{
    Log(lDebug)<<"Executing the TestModel plugin by Totte Karlsson";
    RoadRunner rr;
    rr.load(mModel);

    rr::SimulateOptions opt;
    opt.start       = 0;
    opt.duration    = 10;
    opt.steps       = 14;

    TelluriumData data(rr.simulate(&opt));
    mSimulatedData.setValue(data);

    //Add noise
    const PluginManager* PM = this->getPluginManager();
    Plugin* noise = PM->getPlugin("AddNoise");

    mSimulatedDataWithNoise.setValue(mSimulatedData.getValue());

    noise->setPropertyValue("Sigma", mSigma.getValueHandle());
    noise->setPropertyValue("InputData", mSimulatedDataWithNoise.getValueHandle());
    noise->execute();

    mSimulatedDataWithNoise.setValue(noise->getPropertyValueHandle("InputData"));

    //Add weights
    addWeights();
    return true;
}

void TestModel::addWeights()
{
    TelluriumData &data = * (TelluriumData*) mSimulatedDataWithNoise.getValueHandle();
    if(!data.hasWeights())
    {
        data.allocateWeights();
    }

    double sigma = mSigma;

    for(int r = 0; r < data.rSize(); r++)
    {
        for(int c = 0; c < data.cSize(); c++)
        {
            if( compareNoCase(data.getColumnName(c), "Time") == false )
            {
                double weight = data.getWeight(r,c);
                if(weight == 1)
                {
                    data.setWeight(r,c, weight * sigma * sigma);
                }
                else
                {
                    data.setWeight(r,c, weight + sigma * sigma);
                }
            }
        }
    }
}

// Plugin factory function
Plugin* plugins_cc createPlugin(void* manager)
{
    //allocate a new object and return it
    return new TestModel((PluginManager*) manager);
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

