#ifndef telUtilsExporterH
#define telUtilsExporterH

#if defined(_WIN32)
    #if defined(STATIC_TLPUTILS)
        #define TLPUTILS_DS
    #else
        #if defined(EXPORT_TLPUTILS)
            #define TLPUTILS_DS __declspec(dllexport)
        #else
            #define TLPUTILS_DS __declspec(dllimport)
        #endif
    #endif
#else
    #define TLPUTILS_DS
#endif

#endif

