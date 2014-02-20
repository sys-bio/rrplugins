#include <iostream>
#include "telException.h"
#include "telUtils.h"
#include "telPluginManager.h"
#include "telPlugin.h"
#include "telplugins_c_api.h"
#pragma hdrstop

using namespace std;
using namespace tlp;
using namespace tlpc;
int main()
{
    try
    {
        string fldr(joinPath("..", "plugins"));
        TELHandle pm = createPluginManager(fldr.c_str());

        if(!loadPlugins(pm))
        {
            cout<<getLastError();
        }

        TELHandle aPlugin = getFirstPlugin(pm);

        //Pass a handle of wrong type
        TELHandle aPlugin2 = getFirstPlugin(aPlugin);
        if(!aPlugin2)
        {
            cout<<getLastError();
        }

        //Plugin handles are supported too
        int bad = 123;
        char* name = getPluginName(&bad);
        if(!name)
        {
            cout<<getLastError();
        }


        return 0;
    }
    catch(const std::exception& ex)
    {
        cout<<ex.what();
    }
}
