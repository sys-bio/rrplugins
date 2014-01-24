#ifndef telAPIHandleManagerH
#define telAPIHandleManagerH
#include <map>
//---------------------------------------------------------------------------
//Class keeping track of all handles that are created in the Tellurium C API

using std::map;
//Todo: keep history. If a handle is unregistered, and a later attempt is made
//to use it, we can flag that as an error.
//struct HandleInfo
//{
//    const char* type;
//    bool
//
//};

typedef void* TELHandle;
typedef map<TELHandle, const char*>   HandleMap;

class APIHandleManager
{
    public:
                                        APIHandleManager();
                                       ~APIHandleManager();
        TELHandle                       registerHandle(TELHandle handle,    const char* typeOf);
        bool                            unregisterHandle(TELHandle handle,  const char* typeOf);
        TELHandle                       validate(TELHandle handle,          const char* typeOf, const char* fnc);

    protected:
        HandleMap                       mHandles;

};
#endif
