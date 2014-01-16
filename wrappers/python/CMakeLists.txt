CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(plugins_wrappers)

#=============== INSTALL =====================

FILE (GLOB pyFiles *.py)

install(
        FILES 
        ${pyFiles}
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
