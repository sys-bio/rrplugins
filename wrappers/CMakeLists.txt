CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(plugins_wrappers)

OPTION (TLP_BUILD_PLUGINS_C_API	                        "Build Plugins C API"	            ON)
OPTION (TLP_INSTALL_PLUGINS_PYTHON_API	                "Install Plugins Python API"	    ON)

if(${TLP_BUILD_PLUGINS_C_API} STREQUAL ON)
add_subdirectory("c")
endif()

if(${TLP_INSTALL_PLUGINS_PYTHON_API} STREQUAL ON)
add_subdirectory("python")
endif()


