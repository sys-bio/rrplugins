cmake_minimum_required(VERSION 2.8)
project(plugins)

#Give all plugins access to headers in the following folders
include_directories(
	${TLP_ROOT}/source
	${TLP_ROOT}/wrappers/C
    ${THIRD_PARTY_INSTALL_FOLDER}/include
)

OPTION (TLP_BUILD_TEST_MODEL_PLUGIN	            "Build the Test Model Plugin"	                ON)
OPTION (TLP_BUILD_ADD_NOISE_PLUGIN		        "Build the Add Noise Plugin"	                ON)
OPTION (TLP_BUILD_CHISQUARE_PLUGIN	            "Build the ChiSquare Plugin"	                ON)
OPTION (TLP_BUILD_LEVENBERG_MARQUARDT_PLUGIN	"Build the Levenberg-Marquardt Plugin"	        ON)
OPTION (TLP_BUILD_NELDER_MEAD_PLUGIN	        "Build the Nelder-Mead Plugin"	                ON)
OPTION (TLP_BUILD_MONTE_CARLO_BS_PLUGIN	        "Build the Monte Carlo BS (bootstrap) Plugin"   ON)
#OPTION (TLP_BUILD_AUTO_2000_PLUGIN	            "Build the Auto 2000 Plugin"	                ON)
#OPTION (TLP_BUILD_STAT_PLUGIN	                "Build the STAT (statistics) Plugin"	        ON)

if(${TLP_BUILD_TEST_MODEL_PLUGIN} STREQUAL ON)
    add_subdirectory(test_model)
endif()

if(${TLP_BUILD_ADD_NOISE_PLUGIN} STREQUAL ON)
    add_subdirectory(add_noise)
endif()

if(${TLP_BUILD_CHISQUARE_PLUGIN} STREQUAL ON)
    add_subdirectory(chisquare)
endif()

if(${TLP_BUILD_LEVENBERG_MARQUARDT_PLUGIN} STREQUAL ON)
    add_subdirectory(levenberg_marquardt)
endif()

if(${TLP_BUILD_NELDER_MEAD_PLUGIN} STREQUAL ON)
    add_subdirectory(nelder_mead)
endif()

if(${TLP_BUILD_MONTE_CARLO_BS_PLUGIN} STREQUAL ON)
    add_subdirectory(monte_carlo_bs)
endif()

#if(${TLP_BUILD_AUTO_2000_PLUGIN} STREQUAL ON)
#    add_subdirectory(auto_2000)
#endif()
#
#if(${TLP_BUILD_STAT_PLUGIN} STREQUAL ON)
#    add_subdirectory(statistics)
#endif()
#

#
#
#
