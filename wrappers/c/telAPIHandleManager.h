#ifndef telAPIHandleManagerH
#define telAPIHandleManagerH
#include <map>
//---------------------------------------------------------------------------
//Class keeping track of all handles that are created in the Tellurium C API

using std::map;
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
