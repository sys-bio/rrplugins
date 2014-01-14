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
        DESTINATION site-packages/telplugins  	
        COMPONENT plugins_api
       )


if(WIN32)
    install(
    FILES install_telplugins.py
    DESTINATION site-packages
    COMPONENT tel_plugins
        )
endif(WIN32)
