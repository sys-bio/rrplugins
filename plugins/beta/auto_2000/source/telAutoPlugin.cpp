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

mRRAuto(NULL),
mAutoWorker(*this),
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
//mCalculateSteadyState(              true,                   "CalculateSteadyStateOnInit",                                "fort9",                                                        "",                 ""),
//Pure AUTO parameters
mPrincipalContinuationParameter(    "<none>",               "PrincipalContinuationParameter",       "Principal Continuation Parameter"),

//                                  value,                  name,                                   hint,                                                           descr,              alias,              readonly
mNDIM(                              1,                      "NDIM",                                 "Dimension of the system of equations",                            "",                 ""),
mIPS(                               1,                      "IPS",                                  "Constant defining the problem type",                              "",                 ""),
mIRS(                               0,                      "IRS",                                  "Restart label",                                                   "",                 ""),
mILP(                               1,                      "ILP",                                  "Locate limit points",                                             "",                 ""),
mNICP(                              1,                      "NICP",                                 "Number of free parameters",                                       "",                 ""),
mICP(                               vector<int>(0),         "ICP",                                  "Free parameters",                                                 "",                 ""),
mNTST(                              15,                     "NTST",                                 "Number of mesh intervals",                                        "",                 ""),
mNCOL(                              3,                      "NCOL",                                 "Number of collocation points per mesh interval",                  "",                 ""),
mIAD(                               3,                      "IAD",                                  "Mesh adaption",                                                   "",                 ""),
mISP(                               1,                      "ISP",                                  "Detection of branch points",                                      "",                 ""),
mISW(                               1,                      "ISW",                                  "At a restart solution",                                           "",                 ""),
mIPLT(                              0,                      "IPLT",                                 "The \"principal solution measure\"",                              "",                 ""),
mNBC(                               0,                      "NBC",                                  "Number of boundary conditions",                                   "",                 ""),
mNINT(                              0,                      "NINT",                                 "Number of integral constraints",                                  "",                 ""),
mNMX(                               1000,                   "NMX",                                  "Maximum number of continuation step along any branch",            "",                 ""),
mRL0(                               0.01,                   "RL0",                                  "Principal Continuation Parameter Lower Bound",                    "",                 "PCPLowerBound"              ),
mRL1(                               30,                     "RL1",                                  "Principal Continuation Parameter Upper Bound",                    "",                 "PCPUpperBound"              ),
mA0(                                0,                      "A0",                                   "Bifurcation diagram lower limit for the \"principal solution measure\"",  "",         ""),
mA1(                                10000,                  "A1",                                   "Bifurcation diagram upper limit for the \"principal solution measure\"",  "",         ""),
mNPR(                               50,                     "NPR",                                  "Save the solution in the solution file every NPR continuation steps",                 "",         ""),
mMXBF(                              -1,                     "MXBF",                                 "Maximum number of branch switches",                               "",         ""),
mIID(                               0,                      "IID",                                  "Controls the diagnostic file output",                             "",         ""),
mITMX(                              8,                      "ITMX",                                 "Maximum number of iterations for detecting “special” solutions",  "",         ""),
mITNW(                              5,                      "ITNW",                                 "Maximum number of Newton+Chord iterations",                       "",         ""),
mNWTN(                              3,                      "NWTN",                                 "Maximum number of Newton iterations",                             "",         ""),
mJAC(                               0,                      "JAC",                                  "Jacobian supplied ?",                                             "",         ""),
mEPSL(                              1e-8,                   "EPSL",                                 "Newton/Chord convergence tolerance for free parameters",          "",         ""),
mEPSU(                              1e-8,                   "EPSU",                                 "Newton/Chord convergence tolerance for solutions",                "",         ""),
mEPSS(                              1e-6,                   "EPSS",                                 "Continuation step size tolerance when locating special solutions","",         ""),
mDS(                                0.001,                  "DS",                                   "Nominal continuation step size",                                  "",         ""),
mDSMIN(                             1e-5,                   "DSMIN",                                "Minimum continuation step size",                                  "",         ""),
mDSMAX(                             0.1,                    "DSMAX",                                "Maximum continuation step size",                                  "",         ""),
mIADS(                              1,                      "IADS",                                 "Adapt the continuation step size every IADS steps",               "",         ""),
mNTHL(                              0,                      "NTHL",                                 "The number of modified parameter \"weights\" (for BVP)",          "",         ""),
mTHL(                               vector<int>(0),         "THL",                                  "Parameter index, parameter weight",                               "",         ""),
mNTHU(                              0,                      "NTHU",                                 "The number of modified solution component \"weights\" (for BVP)", "",         ""),
mTHU(                               vector<int>(0),         "THU",                                  "Component index, component weight",                               "",         ""),
mNUZR(                              0,                      "NUZR",                                 "The number of “user output points” specified",                    "",         ""),
mUZR(                               vector<int>(0),         "UZR",                                  "Parameter index, parameter value",                                "",         "")
{
    mVersion = "0.8";

    //Setup the plugin properties
    addProperties();

    //Create a roadrunner to use
    mRR = new RoadRunner;
    mRRAuto.assignRoadRunner(mRR);

    mHint ="BiFurcation Analyis using AUTO2000";
    mDescription="The Auto2000 plugin is a wrapper around the AUTO 2000 BiFurcation analysis library. This plugin was inspired and are using many of Frank Bergmann's \
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

    //Tempfolder setup
    if(getTempFolder() == ".")
    {
        mRR->setTempFileFolder(getCWD());
        mRRAuto.setTempFolder(getCWD());
    }
    else
    {
        mRR->setTempFileFolder(getTempFolder());
        mRRAuto.setTempFolder(getTempFolder());
    }


    //go away and carry out the work
    mAutoWorker.start(inThread);
    return true;
}

void AutoPlugin::addProperties()
{
    mProperties.add(&mTempFolder);
    mProperties.add(&mKeepTempFiles);
    mProperties.add(&mSBML);
    mProperties.add(&mScanDirection);
    mProperties.add(&mPrincipalContinuationParameter);
    mProperties.add(&mFort2);
    mProperties.add(&mFort3);
    mProperties.add(&mFort6);
    mProperties.add(&mFort7);
    mProperties.add(&mFort8);
    mProperties.add(&mFort9);

    //AUTO parameters
    mProperties.add(&mNDIM);
    mProperties.add(&mIPS);
    mProperties.add(&mIRS);
    mProperties.add(&mILP);
    mProperties.add(&mNICP);
    mProperties.add(&mICP);
    mProperties.add(&mNTST);
    mProperties.add(&mNCOL);
    mProperties.add(&mIAD);
    mProperties.add(&mISP);
    mProperties.add(&mISW);
    mProperties.add(&mIPLT);
    mProperties.add(&mNBC);
    mProperties.add(&mNINT);
    mProperties.add(&mNMX);
    mProperties.add(&mRL0);
    mProperties.add(&mRL1);
    mProperties.add(&mA0);
    mProperties.add(&mA1);
    mProperties.add(&mNPR);
    mProperties.add(&mMXBF);
    mProperties.add(&mIID);
    mProperties.add(&mITMX);
    mProperties.add(&mITNW);
    mProperties.add(&mNWTN);
    mProperties.add(&mJAC);
    mProperties.add(&mEPSL);
    mProperties.add(&mEPSU);
    mProperties.add(&mEPSS);
    mProperties.add(&mDS);
    mProperties.add(&mDSMIN);
    mProperties.add(&mDSMAX);
    mProperties.add(&mIADS);
    mProperties.add(&mNTHL);
    mProperties.add(&mTHL);
    mProperties.add(&mNTHU);
    mProperties.add(&mTHU);
    mProperties.add(&mNUZR);
    mProperties.add(&mUZR);
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


