#ifndef rr_auto_exporterH
#define rr_auto_exporterH

#if defined(_WIN32) || defined(__WIN32__)
    #if defined(STATIC_RR_AUTO)
        #define RRA_DECLSPEC
    #else
        #if defined(EXPORT_RR_AUTO)
            #define RRA_DECLSPEC __declspec(dllexport)
        #else
            #define RRA_DECLSPEC __declspec(dllimport)
        #endif
    #endif
#else
    #define RRA_DECLSPEC
#endif

#endif
