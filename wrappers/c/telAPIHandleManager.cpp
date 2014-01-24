#pragma hdrstop
#include <sstream>
#include <exception>
#include "telAPIHandleManager.h"
#include "telException.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace tlp;
APIHandleManager::APIHandleManager()
{


}

APIHandleManager::~APIHandleManager()
{
    //Free any handles in here
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
            msg<<"Got handle of type: "<<it->second<<" Expected type: "<<type;
        }

        throw(BadHandleException(msg.str()));
    }
}

bool APIHandleManager::addHandle(TELHandle handle, const char* type)
{
    mHandles[handle] = type;

    return true;
}
