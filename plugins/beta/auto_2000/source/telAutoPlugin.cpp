#pragma hdrstop
#include <sstream>
#include "telLogger.h"
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"
#include "telAutoPlugin.h"
#include "telUtils.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace tlp;
using namespace telauto;



AutoPlugin::AutoPlugin()
:
CPPPlugin("Auto-2000", "Bifurcation", NULL, NULL),

//PROPERTIES
//                                  value,                  name,                                   hint,                                                           descr,              alias,              readonly

mTempFolder(                        ".",                    "TempFolder",                           "Tempfolder used by auto and roadrunner"),
mKeepTempFiles(                     false,                  "KeepTempFiles",                        "Keep temporary files."),
mSBML(                              "<none>",               "SBML",                                 "SBML, i.e. the model to be used to analyze"),
mScanDirection(                     "Negative",             "ScanDirection",                        "Direction of parameter scan"),

//Output
mCaptureOutputFiles(                false,                  "CaptureOutputFiles",                   "Set flag to true to capture all of Autos output",              "",                 ""),
mFort2(                             "<none>",               "fort2",                                "fort2",                                                        "",                 ""),
mFort3(                             "<none>",               "fort3",                                "fort3",                                                        "",                 ""),
mFort6(                             "<none>",               "BiFurcationSummary",                   "BifurcationSummary",                                           "",                 "BiFurcationSummary"),
mFort7(                             "<none>",               "BiFurcationDiagram",                   "BifurcationDiagram",                                           "",                 "BiFurcationDiagram"),
mFort8(                             "<none>",               "fort8",                                "fort9",                                                        "",                 ""),
mFort9(                             "<none>",               "fort9",                                "fort9",                                                        "",                 ""),

//AUTO parameters
mPrincipalContinuationParameter(    "<none>",               "PrincipalContinuationParameter",       "Principal Continuation Parameter"),
mRL0(                               0,                      "RL0",                                  "Principal Continuation Parameter Lower Bound",                 "",                 "PCPLowerBound"              ),
mRL1(                               0,                      "RL1",                                  "Principal Continuation Parameter Upper Bound",                 "",                 "PCPUpperBound"              ),

mRRAuto(NULL),
mAutoWorker(*this)
{
    mVersion = "0.8";

    //Setup the plugin properties
    mProperties.add(&mTempFolder);
    mProperties.add(&mKeepTempFiles);
    mProperties.add(&mSBML);
    mProperties.add(&mScanDirection);
    mProperties.add(&mPrincipalContinuationParameter);
    mProperties.add(&mRL0);
    mProperties.add(&mRL1);
    mProperties.add(&mFort2);
    mProperties.add(&mFort3);
    mProperties.add(&mFort6);
    mProperties.add(&mFort7);
    mProperties.add(&mFort8);
    mProperties.add(&mFort9);

    //Create a roadrunner to use
    mRR = new RoadRunner;
    mRRAuto.assignRoadRunner(mRR);

    mHint ="BiFurcation Analyis using AUTO2000";
    mDescription="The auto2000 plugin is a wrapper around the AUTO 2000 BiFurcation analysis library. This plugin was inspired and are using many of Frank Bergmann's \
ideas on how to create a usable interface to the AUTO 2000 library.";

}

AutoPlugin::~AutoPlugin()
{
    delete mRR;
}

AutoTellurimInterface& AutoPlugin::getRRAuto()
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

string AutoPlugin::getConstants()
{
    return mRRAuto.getConstantsAsString();
}

bool AutoPlugin::isWorking() const
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
    msg<<mFort7.getValue();
    return msg.str();
}

bool AutoPlugin::execute(bool inThread)
{
    Log(lInfo)<<"Executing the AutoPlugin plugin";
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


