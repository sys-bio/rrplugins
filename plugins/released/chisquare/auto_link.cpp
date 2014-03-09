#if defined(STATIC_PLUGIN)
    #pragma comment(lib, "roadrunner-static.lib")
    #pragma comment(lib, "telplugins-static.lib")
    #pragma comment(lib, "nleq-static.lib")
#else
    #pragma comment(lib, "roadrunner.lib")
    #pragma comment(lib, "telplugins_core.lib")
    #pragma comment(lib, "telplugins_common.lib")
    #pragma comment(lib, "telplugins_math.lib")
#endif

#pragma comment(lib, "poco_foundation-static.lib")



