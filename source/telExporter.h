#ifndef rrpExporterH
#define rrpExporterH

#if defined(_WIN32)
    #if defined(STATIC_PLUGIN_API)
        #define RRP_DECLSPEC
    #else
        #if defined(EXPORT_PLUGIN_API)
            #define RRP_DECLSPEC __declspec(dllexport)
        #else
            #define RRP_DECLSPEC __declspec(dllimport)
        #endif
    #endif
#else
    #define RRP_DECLSPEC
#endif

//Helper macros for plugins
#if defined(_WIN32)
    #if defined(EXPORT_RR_PLUGIN)
        #define RR_PLUGIN_DECLSPEC __declspec(dllexport)
    #else
        #define RR_PLUGIN_DECLSPEC __declspec(dllimport)
    #endif
#else
    #define RR_PLUGIN_DECLSPEC
#endif

//Function calling conventions
#if defined(__BORLANDC__)
    #define call_conv __cdecl
#elif defined(_MSC_VER)
    #define call_conv __cdecl
#else
    #define call_conv
#endif

#endif

