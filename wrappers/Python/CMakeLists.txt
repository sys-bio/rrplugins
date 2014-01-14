CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(plugins_wrappers)

#if(BUILD_TESTS)
#add_subdirectory(Testing)
#endif()

if(INSTALL_EXAMPLES)
add_subdirectory(Examples)
endif()
#=============== INSTALL =====================
install(
        FILES 
        __init__.py
        rrPlugins.py 
        rrPluginUtils.py 
        rrPlugins_CAPI.py 
        rrFindSharedLib.py
        README.txt 
        DESTINATION site-packages/rrplugins  	
        COMPONENT plugins_api
       )


if(WIN32)
    install(
    FILES install_rrplugins.py
    DESTINATION site-packages
    COMPONENT plugins_api
        )
endif(WIN32)
