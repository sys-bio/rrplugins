This directory contains source code for RoadRunners plugin API's, as well as examples and some utility applications.

In order to build the plugin api, using CMake, check the RRP_BUILD_PLUGINS_API.
To build the Plugins C API, check the RRP_BUILD_PLUGINS_C_API.

Actual plugins are built from the plugins folder. 

NOTE: Any CMake flag that is related to the Plugins API is prefixed with "RRP_". 


BUILD_NOTE: The Plugins API require you to have built the RoadRunner core as a shared library.


