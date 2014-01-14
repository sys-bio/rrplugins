cmake_minimum_required(VERSION 2.8)
project(plugins_examples)

if(${TLP_BUILD_EXAMPLES} STREQUAL ON)

#Give access to headers in the following folders
include_directories(
	${TLP_ROOT}/source
	${TLP_ROOT}/wrappers/C
    	${THIRD_PARTY_INSTALL_FOLDER}/include
)

add_subdirectory(c_plugin_demo_1)
add_subdirectory(cpp_plugin_demo_1)

endif() 

install(
    FILES README.txt
    DESTINATION plugins
)
