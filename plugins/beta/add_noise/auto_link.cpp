
#if defined(STATIC_PLUGIN)
    #pragma comment(lib, "roadrunner-static.lib")
    #pragma comment(lib, "telplugins-static.lib")
    #pragma comment(lib, "libsbml-static")
    #if defined(CG_UI)
        #pragma comment(lib, "libxml2_xe.lib")
    #else
        #pragma comment(lib, "libxml2.lib")
    #endif
#else
    #pragma comment(lib, "roadrunner.lib")
    #pragma comment(lib, "telplugins_core.lib")
    #pragma comment(lib, "telplugins_common.lib")
    #pragma comment(lib, "telplugins_math.lib")
#endif

#pragma comment(lib, "poco_foundation-static.lib")



#if defined(_MSC_VER)
#pragma comment(lib, "IPHLPAPI.lib") //Becuase of poco needing this
#endif
