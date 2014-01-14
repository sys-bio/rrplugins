#pragma hdrstop
#include "cpp_plugin_demo.h"
#include "rrRoadRunner.h"
#include <iostream>

//---------------------------------------------------------------------------
namespace cpp_plugin_demo
{
using namespace rr;
using namespace rrp;
using namespace std;

TestPlugin::TestPlugin()
:
CPPPlugin("TestPlugin", "No Category"),
mTestProperty(123, "NrOfIterations", "Hint for Nr of iterations")
{
    mProperties.add( &mTestProperty);
}

TestPlugin::~TestPlugin()
{}

bool TestPlugin::execute(bool inThread)
{
    cout<<"Executing plugin...\n";
    if(mRR)
    {
        StringList aList("S2, S1",", ");
        mRR->setSelections(aList);
    }
    return true;
}

// Plugin raw C functions
TestPlugin* plugins_cc createPlugin()
{
    //allocate a new object and return it
    return new TestPlugin();
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

}

