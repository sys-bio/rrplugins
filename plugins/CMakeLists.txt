cmake_minimum_required(VERSION 2.8)
project(plugins)

#Give all plugins access to headers in the following folders
include_directories(
	${TLP_ROOT}/source
	${TLP_ROOT}/wrappers/C
    ${THIRD_PARTY_INSTALL_FOLDER}/include
)

OPTION (TLP_BUILD_ADD_NOISE_PLUGIN		        "Build the Add Noise Plugin"	                ON)
OPTION (TLP_BUILD_LEVENBERG_MARQUARDT_PLUGIN	"Build the Levenberg-Marquardt Plugin"	        ON)
OPTION (TLP_BUILD_AUTO_2000_PLUGIN	            "Build the Auto 2000 Plugin"	                ON)
OPTION (TLP_BUILD_STAT_PLUGIN	                "Build the STAT (statistics) Plugin"	        ON)
OPTION (TLP_BUILD_CHISQUARE_PLUGIN	            "Build the ChiSquare Plugin"	                ON)
OPTION (TLP_BUILD_SBMLMODEL_PLUGIN	            "Build the SBMLModel Plugin"	                ON)

if(${TLP_BUILD_ADD_NOISE_PLUGIN} STREQUAL ON)
    add_subdirectory(add_noise)
endif()

if(${TLP_BUILD_LEVENBERG_MARQUARDT_PLUGIN} STREQUAL ON)
    add_subdirectory(lmfit)
endif()

if(${TLP_BUILD_AUTO_2000_PLUGIN} STREQUAL ON)
    add_subdirectory(auto_2000)
endif()

if(${TLP_BUILD_STAT_PLUGIN} STREQUAL ON)
    add_subdirectory(stat)
endif()

if(${TLP_BUILD_CHISQUARE_PLUGIN} STREQUAL ON)
    add_subdirectory(chisquare)
endif()

if(${TLP_BUILD_SBMLMODEL_PLUGIN} STREQUAL ON)
    add_subdirectory(sbml_model)
endif()

install(
    FILES README.txt
    DESTINATION plugins
)
