#pragma hdrstop
#include <sstream>
#include <exception>
#include "telAPIHandleManager.h"
#include "telException.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace tlp;
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
        stringstream msg;
        msg<<"Invalid Handle passed to API function: "<<fnc<<endl;

        if(it !=  mHandles.end())
        {
            msg<<"Received handle of type: "<<it->second<<" Expected type: "<<type;
        }

        throw(BadHandleException(msg.str()));
    }
}

bool APIHandleManager::addHandle(TELHandle handle, const char* type)
{
    mHandles[handle] = type;
    return true;
}

bool APIHandleManager::removeHandle(TELHandle handle, const char* type)
{
    HandleMap::iterator it = mHandles.find(handle);
    mHandles.erase ( it, mHandles.end() );
    return true;
}
