cmake_minimum_required(VERSION 2.8)
project(plugins)

#Give all plugins access to headers in the following folders
include_directories(
	${RR_ROOT}/source
	${RR_ROOT}/wrappers/C
	${RR_ROOT}/libplugins/source
	${RR_ROOT}/libplugins/wrappers/C
    ${THIRD_PARTY_INSTALL_FOLDER}/include
)

OPTION (TLP_BUILD_ADD_NOISE_PLUGIN		        "Build Add Noise Plugin"	                ON)
OPTION (TLP_BUILD_LEVENBERG_MARQUARDT_PLUGIN	"Build Levenberg-Marquardt Plugin"	        ON)
OPTION (TLP_BUILD_AUTO_2000_PLUGIN	            "Build Auto 2000 Plugin"	                ON)

if(${TLP_BUILD_ADD_NOISE_PLUGIN} STREQUAL ON)
    add_subdirectory(add_noise)
endif()

if(${TLP_BUILD_LEVENBERG_MARQUARDT_PLUGIN} STREQUAL ON)
    add_subdirectory(lmfit)
endif()

if(${TLP_BUILD_AUTO_2000_PLUGIN} STREQUAL ON)
    add_subdirectory(auto_2000)
endif()


install(
    FILES README.txt
    DESTINATION plugins
)
