CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(plugins_wrappers)

#=============== INSTALL =====================

FILE (GLOB pyFiles tel*.py)

install(
        FILES 
        ${pyFiles}
        __init__.py
        README.txt 
        DESTINATION site-packages/telplugins  	
        COMPONENT telplugins
       )

if(WIN32)
    install(
    FILES install_tellurium_plugins.py
    DESTINATION .
    COMPONENT tel_plugins
        )
endif(WIN32)
