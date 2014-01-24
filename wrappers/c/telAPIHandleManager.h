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

                                       //Used in creation
//        bool                            createHandle(TELHandle handle, HandleType type);
//        bool                            freeHandle(TELHandle handle, HandleType type);

        bool                            addHandle(TELHandle handle, const char* typeOf);
        TELHandle                       validate(TELHandle handle, const char* typeOf, const char* fnc);

    protected:
        HandleMap                       mHandles;

};
#endif
