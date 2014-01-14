#pragma hdrstop
#include <sstream>
#include <string>
#include <iomanip>
#include "Poco/Glob.h"
#include "Poco/SharedLibrary.h"
#include "rrPluginManager.h"
#include "rrPlugin.h"
#include "rrUtils.h"
#include "rrException.h"
#include "rrLogger.h"
#include "rrRoadRunner.h"
#include "rrCPlugin.h"
#include "rrStringList.h"
//---------------------------------------------------------------------------

namespace rrp
{
static bool  hasFileExtension(const string& fName);
static const char* getPluginExtension();
static const char* getPluginPrefix();

#if defined(__BORLANDC__)
    #define exp_fnc_prefix "_"
#else
    #define exp_fnc_prefix ""
#endif

using namespace std;
using namespace rr;
using Poco::SharedLibrary;
using Poco::Glob;

//Convenient function pointers
typedef Plugin*     (*createRRPluginFunc)(PluginManager*);
typedef char*       (*charStarFnc)();
typedef bool        (*setupCPluginFnc)(Plugin*);
typedef bool        (*destroyRRPluginFunc)(Plugin* );

bool destroyRRPlugin(Plugin *plugin);

PluginManager::PluginManager(const std::string& folder)
:
mPluginFolder(folder),
mPluginExtension(getPluginExtension()),
mPluginPrefix(getPluginPrefix())
{}

PluginManager::~PluginManager()
{
    //No matter what.. here shared libs need to be unloaded and deleted
    unloadAll();
}

bool PluginManager::setPluginDir(const string& dir)
{
    mPluginFolder = dir;
    return folderExists(mPluginFolder);
}

string PluginManager::getPluginDir()
{
    return mPluginFolder;
}

string PluginManager::getInfo()
{
    stringstream info;
    info<<setw(30)<<left<<"Plugin Folder: "            <<mPluginFolder<<"\n";
    info<<setw(30)<<left<<"Plugin Extensions: "        <<mPluginExtension<<"\n";
    info<<setw(30)<<left<<"Plugin Prefix: "            <<mPluginPrefix<<"\n";
    info<<setw(30)<<left<<"Number of loaded plugins:"  <<getNumberOfPlugins()<<"\n";

    if(getNumberOfPlugins())
    {
        info<<setw(25)<<left<<"Plugin Names"<<setw(25)<<"Plugin Library Names"<<"\n";
        Plugin* p = getFirstPlugin();

        do
        {
            if(p)
            {
                info<<"  "<<setw(25)<<left<<p->getName()<<setw(25)<<left<<p->getLibraryName()<<"\n";
            }

        } while(p = getNextPlugin());
    }
    return info.str();
}

ostream& operator << (ostream& st, PluginManager& pm)
{
    st<<pm.getInfo();
    return st;
}

Plugin* PluginManager::getFirstPlugin()
{
    mPluginsIter = mPlugins.begin();
    if(mPluginsIter != mPlugins.end())
    {
        return (*mPluginsIter).second;
    }
    return NULL;
}

Plugin* PluginManager::getCurrentPlugin()
{
    if(mPluginsIter != mPlugins.end())
    {
        return (*mPluginsIter).second;
    }
    return NULL;
}

Plugin* PluginManager::getNextPlugin()
{
    if(mPluginsIter != mPlugins.end())
    {
        mPluginsIter++;
        if(mPluginsIter != mPlugins.end())
        {
            return (*mPluginsIter).second;
        }
    }
    return NULL;
}

Plugin* PluginManager::getPreviousPlugin()
{
    if(mPluginsIter != mPlugins.end())
    {
        mPluginsIter--;
        if(mPluginsIter != mPlugins.end())
        {
            return (*mPluginsIter).second;
        }
    }
    return NULL;
}

Plugin* PluginManager::getPlugin(const int& i)
{
    return (*this)[i];
}

Plugin* PluginManager::operator[](const int& i)
{
    if(i >= 0 && i < mPlugins.size())
    {

        return mPlugins[i].second;
    }
    else
    {
        return NULL;
    }
}

int PluginManager::load(const string& pluginName)
{
    Log(lInfo) << "load: " << pluginName;
    int nrOfLoadedPlugins = 0;

    //Throw if plugin folder don't exist
    if(!folderExists(mPluginFolder))
    {
        Log(lError)<<"Plugin folder: "<<mPluginFolder<<" do not exist..";
        throw(Exception("Plugin folder don't exist"));
    }

    set<string> files;
    string globPath =  joinPath(mPluginFolder, "*." + mPluginExtension);

    if(pluginName.size())
    {
        string temp = joinPath(mPluginFolder, pluginName + "." + mPluginExtension);
        files.insert(temp);
     }
    else
    {
        //Get all plugins in plugin folder
        Glob::glob(globPath, files);
    }

    set<string>::iterator it = files.begin();
    //Try to load.. failing to load a plugin do not mean we abort. Catch and report the problem
    for (; it != files.end(); ++it)
    {
        string plugin = getFileName(*it);
        Log(lInfo)<<"Loading plugin: "<<plugin;
        try
        {
            bool res = loadPlugin(plugin);
            if(!res)
            {
                Log(lError)<<"There was a problem loading plugin: "<<plugin;
            }
            nrOfLoadedPlugins++;
        }
        catch(...)
        {
            Log(lError)<<"There was a serious problem loading plugin: "<<plugin;
        }
    }
    return nrOfLoadedPlugins;
}

bool PluginManager::loadPlugin(const string& _libName)
{
    stringstream msg;
    try
    {
        //Make sure the plugin is prefixed with rrp, if not ignore
        //On linux, the plugin is in turn prefixed with "lib"
        string prefix(mPluginPrefix + "rrp_");
        if(_libName.substr(0, prefix.size()) != prefix)
        {
            Log(lWarning)<<"The Plugin: "<<_libName<<" lack the rrp_ prefix. Can't be loaded";
            return false;
        }
        string libName(_libName);
        if(!hasFileExtension(libName))
        {
            libName = libName + "." + getPluginExtension();
        }

        //Check if Plugin is already loaded first
        if(getPlugin(libName))
        {
            Log(lWarning)<<"The Plugin: "<<libName<<" is already loaded";
            return true;
        }

        SharedLibrary *libHandle = new SharedLibrary;
        string fullName = joinPath(mPluginFolder, libName);

        if(!fileExists(fullName))
        {
            Log(lWarning)<<"The Plugin: "<<fullName<<" could not be found";
            return false;
        }
        //This one throws if there is a problem..
        libHandle->load(fullName);

        //Validate the plugin
        if(!checkImplementationLanguage(libHandle))
        {
            stringstream msg;
            msg<<"The plugin: "<<_libName<<" has not implemented the function getImplementationLanguage properly. Plugin can not be loaded";

            throw(msg.str());            
        }

        //Check plugin language
        const char* language = getImplementationLanguage(libHandle);

        if(strcmp(language, "C") == 0)
        {
            //Gather enough library data in order to create a CPlugin object
            //We need at least name, category and an execute function in order to setup a C plugin
            Plugin* aPlugin = createCPlugin(libHandle);
            if(!aPlugin)
            {
                return false;
            }
            aPlugin->setLibraryName(getFileNameNoExtension(libName));

            rrPlugin storeMe(libHandle, aPlugin);
            mPlugins.push_back( storeMe );
            return true;
        }
        else if(libHandle->hasSymbol(string(exp_fnc_prefix) +"createPlugin"))
        {
            createRRPluginFunc create = (createRRPluginFunc) libHandle->getSymbol(string(exp_fnc_prefix) + "createPlugin");

            //This plugin
            Plugin* aPlugin = create(this);
            if(aPlugin)
            {
                aPlugin->setLibraryName(getFileNameNoExtension(libName));

                rrPlugin storeMe(libHandle, aPlugin);
                mPlugins.push_back( storeMe );
            }
            return true;
        }
        else
        {
            stringstream msg;
            msg<<"The plugin library: "<<libName<<" do not have enough data in order to create a plugin. Can't load";
            Log(lWarning)<<msg.str();
            return false;
        }
    }
    //We have to catch exceptions here. Failing to load a plugin should not throw, just return false.
    catch(const string& msg)
    {
        Log(lError)<<"Plugin loading exception: "<<msg;
        return false;
    }
    catch(const Exception& e)
    {
        msg<<"RoadRunner exception: "<<e.what()<<endl;
        Log(lError)<<msg.str();
        return false;
    }
    catch(const Poco::Exception& ex)
    {
        msg<<"Poco exception: "<<ex.displayText()<<endl;
        Log(lError)<<msg.str();
        return false;
    }
    catch(...)
    {
        return false;
    }
}

//Todo: Clean up the unload process..
bool PluginManager::unloadAll()
{
    bool result(true);
    int nrPlugins = getNumberOfPlugins();
    for(int i = 0; i < nrPlugins; i++)
    {
        rrPlugin* aPluginLib = &(mPlugins[i]);
        if(aPluginLib)
        {
            SharedLibrary *pluginLibHandle    = aPluginLib->first;
            Plugin        *aPlugin            = aPluginLib->second;

            destroyRRPlugin(aPlugin);

            //Then unload
            if(pluginLibHandle)
            {
                pluginLibHandle->unload();
                delete pluginLibHandle;
            }
            //And remove from container
            aPluginLib->first = NULL;
            aPluginLib->second = NULL;
            aPluginLib = NULL;
        }
    }

    //Remove all from container...
    mPlugins.clear();
    return result;
}

bool PluginManager::unload(Plugin* plugin)
{
    if(!plugin)
    {
        return unloadAll();
    }

    bool result(false);
    int nrPlugins = getNumberOfPlugins();

    for(vector< rrPlugin >::iterator it = mPlugins.begin(); it != mPlugins.end(); it++)
    {
        rrPlugin *aPluginLib = &(*it);
        if(aPluginLib)
        {
            SharedLibrary *pluginLibHandle    = aPluginLib->first;
            Plugin        *aPlugin            = aPluginLib->second;

            if(aPlugin == plugin)
            {
                destroyRRPlugin(aPlugin);

                plugin = NULL;
                //Then unload
                if(pluginLibHandle)
                {
                    pluginLibHandle->unload();
                    //Research this delete pluginLibHandle;
                }

                //And remove from container
                aPluginLib->first = NULL;
                aPluginLib->second = NULL;
                aPluginLib = NULL;

                //Reset the plugins iterator to a valid one
                mPluginsIter = mPlugins.erase(it);
                result = true;
                break;
            }
        }
    }
    return result;
}

bool PluginManager::checkImplementationLanguage(Poco::SharedLibrary* plugin)
{
    //Check that the plugin has a getImplementationLanguage function
    try
    {
        plugin->getSymbol(string(exp_fnc_prefix) + "getImplementationLanguage");
        return true;
    }
    catch(const Poco::Exception& ex)
    {
        stringstream msg;
        msg<<"Poco exception: "<<ex.displayText()<<endl;
        Log(lError)<<msg.str();
        return false;
    }
}

const char* PluginManager::getImplementationLanguage(Poco::SharedLibrary* plugin)
{
    //Check that the plugin has a getImplementationLanguage function
    try
    {
        charStarFnc func =     (charStarFnc) plugin->getSymbol(string(exp_fnc_prefix) + "getImplementationLanguage");
        return func();
    }
    catch(const Poco::Exception& ex)
    {
        stringstream msg;
        msg<<"Poco exception: "<<ex.displayText()<<endl;
        Log(lError)<<msg.str();
        return NULL;
    }
}

StringList PluginManager::getPluginNames()
{
    StringList names;
    int nrPlugins = getNumberOfPlugins();
    for(int i = 0; i < nrPlugins; i++)
    {
        pair< Poco::SharedLibrary*, Plugin* >  *aPluginLib = &(mPlugins[i]);
        if(aPluginLib)
        {
            Plugin* aPlugin     = aPluginLib->second;
            if(aPlugin)
            {
                names.add(aPlugin->getName());
            }
        }
    }
    return names;
}

StringList PluginManager::getPluginLibraryNames()
{
    StringList names;
    int nrPlugins = getNumberOfPlugins();
    for(int i = 0; i < nrPlugins; i++)
    {
        pair< Poco::SharedLibrary*, Plugin* >  *aPluginLib = &(mPlugins[i]);
        if(aPluginLib)
        {
            Plugin* aPlugin     = aPluginLib->second;
            if(aPlugin)
            {
                names.add(aPlugin->getLibraryName());
            }
        }
    }
    return names;
}

int PluginManager::getNumberOfPlugins()
{
    return mPlugins.size();
}

int PluginManager::getNumberOfCategories()
{
    return -1;
}

Plugin* PluginManager::getPlugin(const string& name)
{
    for(int i = 0; i < getNumberOfPlugins(); i++)
    {
        rrPlugin aPluginLib = mPlugins[i];
        if(aPluginLib.first && aPluginLib.second)
        {
            Plugin* aPlugin = (Plugin*) aPluginLib.second;
            if(aPlugin && aPlugin->getName() == name)
            {
                   return aPlugin;
            }
            if(aPlugin && aPlugin->getLibraryName() == name)
            {
                   return aPlugin;
            }
        }
    }
    return NULL;
}

Plugin* PluginManager::createCPlugin(SharedLibrary *libHandle)
{
    try
    {
        //Minimum bare bone plugin need these
        charStarFnc         getName                 = (charStarFnc) libHandle->getSymbol(string(exp_fnc_prefix) + "getName");
        charStarFnc         getCategory             = (charStarFnc) libHandle->getSymbol(string(exp_fnc_prefix) + "getCategory");

        //All 'data' that we need to create the plugin
        char* name  = getName();
        char* cat   = getCategory();
        CPlugin* aPlugin = new CPlugin(name, cat);

        aPlugin->executeFunction = (executeF)         libHandle->getSymbol(string(exp_fnc_prefix) + "execute");
        aPlugin->destroyFunction = (destroyF)         libHandle->getSymbol(string(exp_fnc_prefix) + "destroyPlugin");
        setupCPluginFnc     setupCPlugin        = (setupCPluginFnc)    libHandle->getSymbol(string(exp_fnc_prefix) + "setupCPlugin");

        //This give the C plugin an opaque Handle to the CPlugin object
        setupCPlugin(aPlugin);
        aPlugin->getCPropertyNames  =    (charStarFnc)      libHandle->getSymbol(string(exp_fnc_prefix) + "getListOfCPluginPropertyNames");
        aPlugin->getCProperty       =    (getAPropertyF)    libHandle->getSymbol(string(exp_fnc_prefix) + "getCPluginProperty");
        return aPlugin;
    }
    catch(const Poco::NotFoundException& ex)
    {
        Log(lError)<<"Error in createCPlugin: " <<ex.message();
        return NULL;
    }
    return NULL;
}


// Plugin cleanup function
bool destroyRRPlugin(Plugin *plugin)
{
    //we allocated in the create function with new, delete the passed object
    try
    {
        delete plugin;
        return true;
    }
    catch(...)
    {
        //Bad stuff!
        clog<<"Failed deleting RoadRunner plugin..";
        return false;
    }
}


const char* getPluginExtension()
{

#if defined(_WIN32)
    return "dll";
#elif defined(__linux__)
    return "so";
#else
    // OSX
    return "dylib";
#endif
}

const char* getPluginPrefix()
{

#if defined(_WIN32)
    return "";
#elif defined(__linux__)
    return "lib";
#else
    return "DEFINE_PLATFORM";
#endif
}

bool hasFileExtension(const string& fName)
{
    return (fName.find_last_of(".") != string::npos) ? true : false;
}

}
