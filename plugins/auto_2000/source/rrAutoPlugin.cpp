#pragma hdrstop
#include <sstream>
#include "rrLogger.h"
#include "rrAutoPlugin.h"
#include "rrc_api.h"
#include "rrc_utilities.h"
#include "rrRoadRunner.h"
#include "rrRoadRunnerData.h"
#include "rrUtils.h"
//---------------------------------------------------------------------------
namespace autoplugin
{

using namespace rrc;
using namespace std;

AutoPlugin::AutoPlugin()
:
CPPPlugin("Auto-2000", "Bifurcation", NULL, NULL),
mTempFolder(                        ".",                    "TempFolder",                                       "Tempfolder used by auto and roadrunner"),
mKeepTempFiles(                     false,                  "KeepTempFiles",                                    "Keep temporary files."),
mSBML(                              "<none>",               "SBML",                                             "SBML, i.e. the model to be used to analyze"),
mScanDirection(                     "Negative",             "ScanDirection",                                    "Direction of parameter scan"),
mPrincipalContinuationParameter(    "<none>",               "PrincipalContinuationParameter",                   "Principal Continuation Property"),
mPCPLowerBound(                     0,                      "PCPLowerBound",                                    "Principal Continuation Parameter Lower Bound"),
mPCPUpperBound(                     0,                      "PCPUpperBound",                                    "Principal Continuation Parameter Upper Bound"),
mBiFurcationDiagram(                "<none>",               "BiFurcationDiagram",                               "BifurcationDiagram"),
mAutoParameters(                    Properties(),           "AutoParameters",                                   "Auto parameter container"),
mRRAuto(NULL),
mAutoWorker(*this)
{
    mVersion = "0.8";
    //Setup the plugins capabilities
    mProperties.add(&mTempFolder);
    mProperties.add(&mKeepTempFiles);
    mProperties.add(&mSBML);
    mProperties.add(&mScanDirection);
    mProperties.add(&mPrincipalContinuationParameter);
    mProperties.add(&mPCPLowerBound);
    mProperties.add(&mPCPUpperBound);
    mProperties.add(&mBiFurcationDiagram);
    mProperties.add(&mAutoParameters);

    //Create a roadrunner to use
    mRR = new RoadRunner;
    mRRAuto.assignRoadRunner(mRR);

    mHint ="BiFurcation Analyis using AUTO2000";
    mDescription="The auto2000 plugin is a wrapper around the AUTO 2000 BiFurcation analysis library. This plugin was inspired and are using many of Frank Bergmann's \
ideas on how to create a usable interface to the AUTO 2000 library.";

    //Populate auto parameters
//    InputConstants& ic = mRRAuto.getInputConstants();

//    Properties &paras = *(Properties*) mAutoParameters.getValueHandle();
//    paras.add(&(ic.RL0));
}

AutoPlugin::~AutoPlugin()
{
    delete mRR;
}

RRAuto& AutoPlugin::getRRAuto()
{
    return mRRAuto;
}

void AutoPlugin::setScanDirection(ScanDirection dir)
{
    if(dir == sdPositive)
    {
        mScanDirection.setValue("Positive");
    }
    else
    {
        mScanDirection.setValue("Negative");
    }
}

void AutoPlugin::setPrincipalContinuationParameter(const string& para)
{
    mPrincipalContinuationParameter.setValue(para);
}

void AutoPlugin::setPCPLowerBound(double val)
{
    mPCPLowerBound.setValue(val);
}

void AutoPlugin::setPCPUpperBound(double val)
{
    mPCPUpperBound.setValue(val);
}

void AutoPlugin::setSBML(const string& val)
{
    mSBML.setValue(val);
}

string AutoPlugin::getConstants()
{
    return mRRAuto.getConstantsAsString();
}

bool AutoPlugin::isWorking()
{
    return mAutoWorker.isRunning();
}

string AutoPlugin::getStatus()
{
    stringstream msg;
    msg<<Plugin::getStatus();
    msg<<"TempFolder: "<<mTempFolder<<"\n";
    return msg.str();
}

bool AutoPlugin::resetPlugin()
{
    if(mAutoWorker.isRunning())
    {
        return false;
    }

    return true;
}

string AutoPlugin::getTempFolder()
{
    return mTempFolder.getValue();
}

string AutoPlugin::getSBML()
{
    return mSBML.getValue();
}

string AutoPlugin::getResult()
{
    stringstream msg;
    msg<<"AUTO 2000 DATA\n";
    msg<<mBiFurcationDiagram.getValue();
    return msg.str();
}

bool AutoPlugin::execute(bool inThread)
{
    Log(rr::lInfo)<<"Executing the AutoPlugin plugin";
    //go away and carry out the work
    mAutoWorker.start(inThread);
    return true;
}

//Functions allowing the plugin to be loaded by plugin manager
AutoPlugin* auto_cc createPlugin()
{
    //allocate a new object and return it
    return new AutoPlugin;
}

const char* auto_cc getImplementationLanguage()
{
    return "CPP";
}

}

