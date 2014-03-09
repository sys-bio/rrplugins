cmake_minimum_required(VERSION 2.8)
project(plugins)

#Give all plugins access to headers in the following folders
include_directories(
    ${TLP_ROOT}/source/core
    ${TLP_ROOT}/source/common
    ${TLP_ROOT}/source/math
	${TLP_ROOT}/wrappers/C
    ${THIRD_PARTY_INSTALL_FOLDER}/include
)

OPTION (TLP_BUILD_BETA_PLUGINS		            "Build plugins currently in Beta development state"	                ON)

if(${TLP_BUILD_BETA_PLUGINS} STREQUAL ON)
    add_subdirectory(beta)
endif()

    add_subdirectory(released)
install(
    FILES README.txt
    DESTINATION plugins
)
