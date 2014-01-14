CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(plugins_wrappers)

#=============== INSTALL =====================
install(
        FILES 
        __init__.py
        telPlugins.py 
        telPluginUtils.py 
        telPlugins_CAPI.py 
        telFindSharedLib.py
        README.txt 
        DESTINATION site-packages/telplugins  	
        COMPONENT telplugins
       )


if(WIN32)
    install(
    FILES install_telplugins.py
    DESTINATION site-packages
    COMPONENT tel_plugins
        )
endif(WIN32)
