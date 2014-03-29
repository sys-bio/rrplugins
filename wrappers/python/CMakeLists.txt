CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(plugins_wrappers)

#=============== INSTALL =====================

FILE (GLOB pyFiles tel*.py)

install(
        FILES 
        ${pyFiles}
        __init__.py
        README.txt 
        DESTINATION site-packages/teplugins  	
        COMPONENT telplugins
       )


