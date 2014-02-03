#if defined(STATIC_PLUGIN)
    #pragma comment(lib, "roadrunner-static.lib")
    #pragma comment(lib, "telplugins-static.lib")
    #pragma comment(lib, "nleq-static.lib")
#else
    #pragma comment(lib, "roadrunner.lib")
    #pragma comment(lib, "telplugins.lib")
#endif

#pragma comment(lib, "poco_foundation-static.lib")



