#pragma hdrstop
#include <sstream>
#include <exception>
#include "rr/rrLogger.h"
#include "telAPIHandleManager.h"
#include "telException.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace tlp;
using namespace rr;
APIHandleManager::APIHandleManager()
{}

APIHandleManager::~APIHandleManager()
{
    //Report existence of any handles in here.. that would be a memory leak if so
}

TELHandle APIHandleManager::validate(TELHandle handle, const char* type, const char* fnc)
{
    HandleMap::iterator it = mHandles.find(handle);

    if(it !=  mHandles.end() && it->second == type)
    {
        return handle;
    }
    else
    {
        //Todo later: if an object of type B, derived from A is registered in the handles container, a passed handle of
        //type A should be validated as OK.
        stringstream msg;
        msg<<"Questionable Handle passed to API function: "<<fnc<<endl;

        if(it !=  mHandles.end()) //Found a registered handle with proper address, but types differ.
        {
            string allowed("Property");
            if(strstr(it->second, allowed.c_str()) != NULL)
            {
                //For now don't check ParameterBase types. See todo above
                msg<<"Received handle of type: "<<it->second<<" but expected type: "<<type;
                Log(lDebug)<<msg.str();
                return handle;
            }
            else
            {
                msg<<"Received handle of type: "<<it->second<<" but expected type: "<<type;
                throw(BadHandleException(msg.str()));
            }
        }
        else
        {
            msg<<"Invalid Handle passed to API function: "<<fnc<<endl;
            throw(BadHandleException(msg.str()));
        }
    }
}

TELHandle APIHandleManager::registerHandle(TELHandle handle, const char* type)
{
    //Could check for duplicates and signal if that happens
    if(handle)
    {
        mHandles[handle] = type;
    }

    return handle;
}

bool APIHandleManager::unregisterHandle(TELHandle handle, const char* type)
{
    HandleMap::iterator it = mHandles.find(handle);
    mHandles.erase ( it, mHandles.end() );
    return true;
}


