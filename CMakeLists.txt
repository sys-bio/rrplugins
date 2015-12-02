cmake_minimum_required(VERSION 2.8)
project(telplugins)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Variables used in project
set(TLP_GENERATED_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/source)
set(TLP_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(TLP_DEPENDENCIES_PATH "" CACHE PATH "Path to TelPlugins dependencies")

message( STATUS "TLP_DEPENDENCIES_PATH = \"${TLP_DEPENDENCIES_PATH}\"" )
if( TLP_DEPENDENCIES_PATH STREQUAL "" )
  message( FATAL_ERROR "Please set TLP_DEPENDENCIES_PATH to point to the directory containing third-party dependencies" )
elseif( NOT IS_DIRECTORY "${TLP_DEPENDENCIES_PATH}/include/Poco" )
  message( FATAL_ERROR "TLP_DEPENDENCIES_PATH is missing include/Poco" )
elseif( NOT EXISTS "${TLP_DEPENDENCIES_PATH}/include/Poco/Foundation.h" OR 
        IS_DIRECTORY "${TLP_DEPENDENCIES_PATH}/include/Poco/Foundation.h" )
  message( FATAL_ERROR "Could not find Foundation.h in TLP_DEPENDENCIES_PATH/include/Poco" )
endif()

# Feature selection
set ( TLP_BUILD_SHARED_LIB ON  CACHE BOOL   "Build shared library" )
set ( TLP_BUILD_STATIC_LIB ON  CACHE BOOL   "Build static library" )
set ( TLP_BUILD_APPS       ON  CACHE BOOL   "Build apps" )
set ( TLP_BUILD_EXAMPLES   OFF CACHE BOOL   "Build examples" )
set ( TLP_BUILD_TEST_TOOLS OFF CACHE BOOL   "Build test tools" )

set(TLP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Using third party library prefix of ${THIRD_PARTY_INSTALL_FOLDER}")
message(STATUS "Installing TelluriumPlugins to ${CMAKE_INSTALL_PREFIX}")

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

    Features:
      Enable shared library?    ${TLP_BUILD_SHARED_LIB}
      Enable static library?    ${TLP_BUILD_STATIC_LIB}
      Enable apps?              ${TLP_BUILD_APPS}
      Enable examples?          ${TLP_BUILD_EXAMPLES}
      Enable test tools?        ${TLP_BUILD_TEST_TOOLS}
      
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

if(TLP_BUILD_APPS)
    add_subdirectory(apps)
endif()

if(TLP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_subdirectory(wrappers)

if(TLP_BUILD_TEST_TOOLS)
    message(STATUS "building tests")
    add_subdirectory(testing)
else()
    message(STATUS "NOT building tests")
endif(TLP_BUILD_TEST_TOOLS)


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

