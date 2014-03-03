#pragma hdrstop
#include <sstream>
#include "telLogger.h"
#include "telException.h"
#include "rr/rrRoadRunner.h"
#include "lmfit_doc.h"
#include "lm.h"
#include "telTelluriumData.h"
#include "telUtils.h"
//---------------------------------------------------------------------------

//Below defines are from the LMFIT lib.. convert to constants later on
/* machine-dependent constants from float.h */
#define LM_MACHEP     DBL_EPSILON   /* resolution of arithmetic */
#define LM_DWARF      DBL_MIN       /* smallest nonzero number */
#define LM_SQRT_DWARF sqrt(DBL_MIN) /* square should not underflow */
#define LM_SQRT_GIANT sqrt(DBL_MAX) /* square should not overflow */
#define LM_USERTOL    30*LM_MACHEP  /* users are recommended to require this */

namespace lmfit
{
using namespace std;
using tlp::StringList;

LM::LM(PluginManager* manager)
:
CPPPlugin(                      "Levenberg-Marquardt", "Fitting",       NULL, manager),

//Properties.                   //value,                name,                                   hint,                                                           description, alias, readonly);
mSBML(                          "<none>",               "SBML",                                 "SBML document as a string. Model to be used in the fitting"),
mExperimentalData(              TelluriumData(),        "ExperimentalData",                     "Data object holding Experimental data: Provided by client"),
mModelData(                     TelluriumData(),        "FittedData",                           "Data object holding model data: Handed to client"),
mResidualsData(                 TelluriumData(),        "Residuals",                            "Data object holding residuals: Handed to client", "", "", true),
mInputParameterList(            Properties(),           "InputParameterList",                   "List of parameters to fit"),
mOutputParameterList(           Properties(),           "OutputParameterList",                  "List of parameters that was fitted"),
mConfidenceLimits(              Properties(),           "ConfidenceLimits",                     "Confidence limits for each parameter"),
mExperimentalDataSelectionList( StringList(),           "ExperimentalDataSelectionList",        "Experimental data selection list"),
mModelDataSelectionList(        StringList(),           "FittedDataSelectionList",              "Fitted data selection list"),
mNorm(                          0,                      "Norm",                                 "Norm of fitting. An estimate of goodness of fit"),
mNorms(                         TelluriumData(),        "Norms",                                "Norms from fitting session.", "", "", true),
mNrOfIter(                      0,                      "NrOfIter",                             "Number of iterations"),

mStandardizedResiduals(         TelluriumData(),        "StandardizedResiduals",                "Standarized residuals.", "", "", true),
mNormalProbabilityOfResiduals(  TelluriumData(),        "NormalProbabilityOfResiduals",         "Normal Probability of Residuals.", "", "", true),
mChiSquare(                     0,                      "ChiSquare",                            "Chi-Square after fitting", "", "", true),
mReducedChiSquare(              0,                      "ReducedChiSquare",                     "Reduced Chi-Square after fitting", "", "", true),


//The following Properties are the members of lmfits control_structure.
//Changing their default values may be needed depending on the problem.
ftol(                           LM_USERTOL,              "ftol"       ,                         "Relative error desired in the sum of squares. "),
xtol(                           LM_USERTOL,              "xtol"       ,                         "Relative error between last two approximations. "),
gtol(                           LM_USERTOL,              "gtol"       ,                         "Orthogonality desired between fvec and its derivs. "),
epsilon(                        LM_USERTOL,              "epsilon"    ,                         "Step used to calculate the jacobian. "),
stepbound(                      100.,                    "stepbound"  ,                         "Initial bound to steps in the outer loop. "),
patience(                       100,                     "patience"    ,                        "Maximum number of iterations as patience*(nr_of_parameters +1). "),
mWorker(*this),
mLMData(mWorker.mLMData),
rNormsData(mNorms.getValueReference())
{
    mVersion = "0.8";

    //Add plugin properties to property container
    mProperties.add(&mSBML);
    mProperties.add(&mExperimentalData);
    mProperties.add(&mModelData);
    mProperties.add(&mResidualsData);
    mProperties.add(&mInputParameterList);
    mProperties.add(&mOutputParameterList);
    mProperties.add(&mConfidenceLimits);
    mProperties.add(&mExperimentalDataSelectionList);
    mProperties.add(&mModelDataSelectionList);
    mProperties.add(&mNorm);
    mProperties.add(&mNorms);
    mProperties.add(&mNrOfIter);
    mProperties.add(&mStandardizedResiduals);
    mProperties.add(&mNormalProbabilityOfResiduals);
    mProperties.add(&mChiSquare);
    mProperties.add(&mReducedChiSquare);

    //Add the lmfit parameters
    mProperties.add(&ftol);
    mProperties.add(&xtol);
    mProperties.add(&gtol);
    mProperties.add(&epsilon);
    mProperties.add(&stepbound);
    mProperties.add(&patience);

    //Allocate model and Residuals data
    mResidualsData.setValue(new TelluriumData());
    mModelData.setValue(new TelluriumData());

    mHint ="Parameter fitting using the Levenberg-Marquardt algorithm";
    mDescription="The Levenberg-Marquardt plugin is used to fit a proposed \
SBML models parameters to experimental data. \
The current implementation is based on the lmfit C library by Joachim Wuttke. \
The Plugin has numerous parameters for fine tuning the algorithm. See the embedded PDF for more information. \
";
    //The function below assigns property descriptions
    assignPropertyDescriptions();
}

LM::~LM()
{}

bool LM::isWorking() const
{
    return mWorker.isRunning();
}

unsigned char* LM::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int LM::getPDFManualByteSize()
{
    return sizeofPDF;
}

StringList LM::getExperimentalDataSelectionList()
{
    return mExperimentalDataSelectionList.getValue();
}

string LM::getStatus()
{
    stringstream msg;
    msg<<Plugin::getStatus();    
    
    msg<<"\nFitting parameters: "<<mInputParameterList;
    msg <<getResult();    
    return msg.str();
}

string LM::getImplementationLanguage()
{
    return lmfit::getImplementationLanguage();
}

bool LM::resetPlugin()
{
    if(mWorker.isRunning())
    {
        return false;
    }

    mTerminate = false;
    mInputParameterList.getValueReference().clear();
    mOutputParameterList.getValueReference().clear();
    mExperimentalDataSelectionList.getValueReference().clear();
    mModelDataSelectionList.getValueReference().clear();

    //Clear data
    mExperimentalData.clearValue();
    mModelData.clearValue();
    mNrOfIter.clearValue();
    mNorms.clearValue();
    mResidualsData.clearValue();

    return true;
}

string LM::getSBML()
{
    return mSBML.getValue();
}

string LM::getResult()
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

    msg<<"Norm: "<<mNorm.getValue()<<endl;
    msg<<"Chi Square: "<<mChiSquare.getValue()<<endl;
    msg<<"Reduced Chi Square: "<<mReducedChiSquare.getValue()<<endl;
    return msg.str();
}

bool LM::execute(bool inThread)
{
    try
    {
        Log(lInfo)<<"Executing the LM plugin";
        mWorker.start(inThread);
        return true;
    }
    catch(const Exception& ex)
    {
        Log(lError) << "There was a problem in the execute of the LMFIT plugin: " << ex.getMessage();
        throw(ex);
    }
    catch(...)
    {
        Log(lError) << "There was an unknown problem in the execute of the LMFIT plugin.";
        throw("There was an unknown problem in the execute of the LMFIT plugin.");
    }
}

// Plugin factory function
LM* plugins_cc createPlugin(void* manager)
{
    //allocate a new object and return it
    return new LM((PluginManager*) manager);
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

void LM::assignPropertyDescriptions()
{
    stringstream s;
s << "The SBML property should be assigned the (XML) \
text that defines the SBML model that is used to fit parameters.";
mSBML.setDescription(s.str());
s.str("");

s << "Experimental data contains the data to be used for fitting input.";
mExperimentalData.setDescription(s.str());
s.str("");

s << "Model data is calculated after the fitting algorithm finishes. It uses the obtained model parameters as input.";
mModelData.setDescription(s.str());
s.str("");

s << "Residuals data contains the differencies between the Experimental data and the ModelData.";
mResidualsData.setDescription(s.str());
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

s << "The norm is a readonly output variable indicating the goodness of fit. The smaller value, the better fit.";
mNorm.setDescription(s.str());
s.str("");

s << "The norm is calculated throughout a fitting session. Each Norm value is stored in the Norms (readonly) variable.";
mNorms.setDescription(s.str());
s.str("");

s << "The number of iterations wil hold the number of iterations of the internal fitting routine.";
mNrOfIter.setDescription(s.str());
s.str("");

    //Add the lmfit parameters
s << "ftol is a nonnegative input variable. Termination occurs when \
both the actual and predicted relative reductions in the sum \
of squares are at most ftol. Therefore, ftol measures the \
relative error desired in the sum of squares.";
    ftol.setDescription(s.str());
s.str("");

s << "xtol is a nonnegative input variable. Termination occurs when \
the relative error between two consecutive iterates is at \
most xtol. Therefore, xtol measures the relative error desired \
in the approximate solution.";
xtol.setDescription(s.str());
s.str("");

s << "gtol is a nonnegative input variable. Termination occurs when \
the cosine of the angle between fvec and any column of the \
jacobian is at most gtol in absolute value. Therefore, gtol \
measures the orthogonality desired between the function vector \
and the columns of the jacobian.";
    gtol.setDescription(s.str());
s.str("");

s << "Step used to calculate the Jacobian.";
    epsilon.setDescription(s.str());
s.str("");

s << "Initial bound to steps in the outer loop.";
    stepbound.setDescription(s.str());
s.str("");

s << "Maximum number of iterations.";
    patience.setDescription(s.str());
s.str("");

}

}

