#ifndef telAPIHandleManagerH
#define telAPIHandleManagerH
#include <map>
//---------------------------------------------------------------------------
//Class keeping track of all handles that are created in the Tellurium C API

using std::map;

typedef void* TELHandle;
//enum HandleType {htPropertiesHandle = 0, htPropertyHandle, htPluginHandle, htPluginManagerHandle, htDataHandle, htUnKnown};
typedef map<TELHandle, const char*>   HandleMap;

class APIHandleManager
{
    public:
                                        APIHandleManager();
                                       ~APIHandleManager();
        bool                            addHandle(TELHandle handle, const char* typeOf);
        bool                            removeHandle(TELHandle handle, const char* typeOf);
        TELHandle                       validate(TELHandle handle, const char* typeOf, const char* fnc);

    protected:
        HandleMap                       mHandles;

};
#endif
