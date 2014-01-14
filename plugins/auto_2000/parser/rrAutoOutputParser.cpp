#pragma hdrstop
#include "rrLogger.h"
#include "rrAutoOutputParser.h"
#include "rrc_api.h"
#include "rrc_utilities.h"
#include "rrRoadRunner.h"
#include "rrRoadRunnerData.h"
#include "rrUtils.h"
//---------------------------------------------------------------------------
namespace autoplugin
{

using namespace rr;
using namespace rrc;

AutoOutputParser::AutoOutputParser()
:
CPPPlugin("AutoOutputParser", "Bifurcation", NULL, NULL),
//The Capability
mAutoOutputParser(              "AutoOutputParser",                     "<none>",               "Bifurcation"),
mBiFurcationDiagram(            "BiFurcationDiagram",                   "<none>",               "BifurcationDiagram"),
mLabeledSolutionPoints(         "LabeledSolutionPoints",                StringList(),               "Special, Labeled solution points"),
mAutoOutputParserWorker(*this)
{
    //Setup the plugins capabilities
    mAutoOutputParser.addParameter(&mBiFurcationDiagram);
    mAutoOutputParser.addParameter(&mLabeledSolutionPoints);
    mCapabilities.add(mAutoOutputParser);
}

AutoOutputParser::~AutoOutputParser()
{}


bool AutoOutputParser::isWorking()
{
    return mAutoOutputParserWorker.isRunning();
}

string AutoOutputParser::getStatus()
{
    stringstream msg;
    msg<<Plugin::getStatus();
    return msg.str();
}

bool AutoOutputParser::resetPlugin()
{
    if(mAutoOutputParserWorker.isRunning())
    {
        return false;
    }

    return true;
}

string AutoOutputParser::getResult()
{
    stringstream msg;

//    msg<<data;
    return msg.str();
}

bool AutoOutputParser::setInputData(void* inputData)
{
    return true;
}

bool AutoOutputParser::execute(void* inputData, bool useThread)
{
    Log(lInfo)<<"Executing the AutoOutputParser plugin";

    //go away and carry out the work in a thread
    //Assign callback functions to communicate the progress of the thread
    mAutoOutputParserWorker.assignCallBacks(mWorkStartedCB, mWorkFinishedCB, mUserData);

    //Check if inputData is supplied
    if(inputData)
    {
        //It HAS to be a Parameter<string>
        Parameter<string> &para = *((Parameter<string>*) inputData);
        mBiFurcationDiagram.setValue( para.getValue());
    }
    mAutoOutputParserWorker.start(useThread);
    return true;
}

// Plugin factory function
AutoOutputParser* plugins_cc createPlugin(rr::RoadRunner* aRR, const PluginManager* pm)
{
    //allocate a new object and return it
    return new AutoOutputParser();
}


const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

}

