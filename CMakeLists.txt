cmake_minimum_required(VERSION 2.8)
project(telplugins)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(TLP_GENERATED_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/source)
set(TLP_ROADRUNNER_INSTALL_PATH ${CMAKE_INSTALL_PREFIX})
set(TLP_ROADRUNNER_INSTALL_LIB_PATH ${TLP_ROADRUNNER_INSTALL_PATH}/lib)
set(TLP_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

OPTION (INSTALL_APPS            "Build and Install Apps"                         ON )
OPTION (INSTALL_STATIC_LIB      "Install TelluriumPlugins CXX Static Lib"        OFF)
OPTION (TLP_BUILD_SHARED_CORE   "Build TelluriumPlugins Core Shared Library"     ON)
OPTION (INSTALL_EXAMPLES        "Build and Install Tellurium Plugin Examples"    OFF)
OPTION (BUILD_TEST_TOOLS        "Build Tellurium Plugins Test Tools"             OFF)

set(TLP_ROOT                     ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Using third party library prefix of ${THIRD_PARTY_INSTALL_FOLDER}")
message(STATUS "Installing TelluriumPlugins to ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "Choose the build type. The options are: None (CMAKE_CXX_FLAGS or
     CMAKE_C_FLAGS are used), Debug, Release, RelWithDebInfo, MinSizeRel.")
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the build type. The options are: None (CMAKE_CXX_FLAGS or
  CMAKE_C_FLAGS are used), Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)
endif()

IF(WIN32)
    IF(${MSVC})
        IF(CMAKE_BUILD_TYPE MATCHES "Debug")
            set(exe_path ${exe_path}/Debug)
            set(lib_path ${lib_path}/Debug)
        ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
               set(exe_path ${exe_path}/Release)
               set(lib_path ${lib_path}/Release)
        ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")
    ELSE(WIN32)
   # Linux
    ENDIF(${MSVC})
ENDIF(WIN32)

# TODO libxml2 handling is excedingly hackish, it is all homegrown
# manually linking crap, need to fix this!

#NOTE:  if fixed here, need to make the same fix in roadrunner/CMakeLists.txt

if (WIN32)
    message(STATUS "adding ${THIRD_PARTY_INSTALL_FOLDER}/include/libxml2 to include path")
    include_directories(${THIRD_PARTY_INSTALL_FOLDER}/include/libxml2)
else()
    #UNIX
    find_package(LibXml2 REQUIRED)
	message(STATUS "found libxml2, include dir: ${LIBXML2_INCLUDE_DIR}") 
	include_directories(${LIBXML2_INCLUDE_DIR})
endif(WIN32)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/bin)

include_directories(
    ${TLP_ROOT}
    ${TLP_ROOT}/manager
    ${THIRD_PARTY_INSTALL_FOLDER}/include
)

link_directories (
    ${THIRD_PARTY_INSTALL_FOLDER}/lib
)
if(${MSVC})
    add_definitions(
        -DPOCO_NO_AUTOMATIC_LIBS
        -DCRT_NONSTDC_NO_DEPRECATE
        -D_CRT_SECURE_NO_WARNINGS    #MS wanting you to changes basically all standard C functions :(
        )
        
    #  4251 About exporting std classes
    #  4018 Comparing unsigned/signed ints
    #  4996 Deprecated functions   
    add_definitions( "/wd4251 /wd4018 /wd4996 /nologo" )   

    SET (CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS} /EHsc ")
    SET (CMAKE_SHARED_LINKER_FLAGS     "${CMAKE_SHARED_LINKER_FLAGS} ") #/FORCE:MULTIPLE")

endif()

#=== COMPILER FLAGS
if(${BORLAND})
add_definitions(
    -DUSE_PCH                   #Enable pre-compiled headers
    -H=${PROJECT_BINARY_DIR}/rr_pch.csm
    -w-8012                     #Comparing signed /unsigned
    -w-8057                     #Parameter never used
    -w-8004                     #'var' is assigned a value that is never used
    )
endif()

if(UNIX)
    if(CMAKE_COMPILER_IS_GNUCXX)
        set (CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} -fPIC")
        set (CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} -fPIC")
    endif()
endif()

message(STATUS "
-------------------------------------------------------------------------------
TelPlugins
-------------------------------------------------------------------------------

    For up-to-date news, releases, and documentation, please visit:
    http://libroadrunner.org/

    Configured on host $ENV{COMPUTERNAME} ${HOSTNAME}
      host OS                   ${CMAKE_SYSTEM_NAME}
      host architecture         ${CMAKE_SYSTEM_PROCESSOR}

    General flags:
      CC                        ${CMAKE_C_COMPILER}
      CXX (not used)            ${CMAKE_CXX_COMPILER}
      CFLAGS                    ${CMAKE_C_FLAGS}
      CXXFLAGS                  ${CMAKE_CXX_FLAGS}
      LDFLAGS                   ${CMAKE_EXE_LINKER_FLAGS}

    Installation prefix:        ${CMAKE_INSTALL_PREFIX}

    Dependencies (packages marked with *** are required):
    "
)


add_subdirectory(source)
add_subdirectory(plugins)
add_subdirectory(scripts)

if(INSTALL_APPS)
    add_subdirectory(apps)
endif()

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

add_subdirectory(wrappers)

if(BUILD_TEST_TOOLS)
    message(STATUS "building tests")
    add_subdirectory(testing)
else()
    message(STATUS "NOT building tests")
endif(BUILD_TEST_TOOLS)


#======================= INSTALL STUFF ============================
#Install the "installer". Can make this more elegant later on
FILE (GLOB installerFiles installer/windows/*.*)
install ( FILES 
${installerFiles} 
DESTINATION ./installer/windows
)

#Install createPythonReleaseScript
install (
FILES scripts/createPythonRelease.sh
DESTINATION ./../
)
#=== ThirdParties
if(${BORLAND})
    set(CG_RUNTIMES        cc32110MT.dll)
    foreach(runtime ${CG_RUNTIMES})
        install (FILES
            ${THIRD_PARTY_FOLDER}/dependencies/cg/xe/${runtime}
            DESTINATION bin
            COMPONENT rr_core)
    endforeach()
endif()

install(
    FILES     
    README.txt 
    LICENSE.txt 
    AUTHORS.txt 
    FUNDING.txt
    VERSION.txt
    NEWS.txt
    NOTICE.txt
    CHANGELOG.txt
    DESTINATION .
)

