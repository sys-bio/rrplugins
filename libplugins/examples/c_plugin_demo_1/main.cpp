/**
 * @file main.cpp
 * @brief Example demonstrating usage of a plugin written in C
 * @author Totte Karlsson
 *
 * <hr>
 * This file is part of cRoadRunner.
 * See http://code.google.com/p/roadrunnerlib for more details.
 *
 * Copyright (C) 2012-2013
 *   University of Washington, Seattle, WA, USA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * In plain english this means:
 *
 * You CAN freely download and use this software, in whole or in part, for personal,
 * company internal, or commercial purposes;
 *
 * You CAN use the software in packages or distributions that you create.
 *
 * You SHOULD include a copy of the license in any redistribution you may make;
 *
 * You are NOT required include the source of software, or of any modifications you may
 * have made to it, in any redistribution you may assemble that includes it.
 *
 * YOU CANNOT:
 *
 * redistribute any piece of this software without proper attribution;
*/
#include <iostream>
#include "rrStringList.h"
#include "rrc_api.h"
#include "rrplugins_c_api.h"
using namespace rr;
using namespace rrc;
using namespace rrp;
using namespace std;

int main()
{
    try
    {
        RRPluginManagerHandle pm = createPluginManager("..\\plugins");
        int nrOfPlugins = loadPlugins(pm);
        if(!nrOfPlugins)
        {
            throw("No plugins was loaded");
        }

        //Retrieve a handle to the C plugin demo
        RRPluginHandle plugin = getPlugin(pm, "C Plugin Demo");
        if(!plugin)
        {
            throw("Demo plugin could not be loaded");
        }

        char* pluginInfo = getPluginInfo(plugin);
        if(pluginInfo)
        {
            cout<<pluginInfo;
            rrc::freeText(pluginInfo);
        }

        //Retrieve any properties that the plugin has
        char* properties = getListOfPluginPropertyNames(plugin);
        if(!properties)
        {
            throw("Plugin do not have any properties. For this demo, this is an error!");
        }

        StringList propNames(properties, ",");

        for(int i = 0; i < propNames.size(); i++)
        {
            cout << propNames[i] << endl;
        }

        //We know the name of the Demo property, being "Demo Property"
        RRPropertyHandle prop = getPluginProperty(plugin, "Demo Property");
        if(prop)
        {
            cout << "Before execute: "<<getPropertyValueAsString(prop)<<endl;
        }

        if(!executePlugin(plugin))
        {
            throw("There was a problem executing the plugin...");
        }

        if(prop)
        {
            cout << "After execute: "<<getPropertyValueAsString(prop)<<endl;
        }

        //This will unload all plugins..
        freePluginManager(pm);
    }
    catch(const char* msg)
    {
        clog<<"There was a problem: "<<msg;
    }
    return 0;
}



