cmake_minimum_required(VERSION 3.2)
project(rrplugins)

# Add local modules to CMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Variables used in project
set ( TLP_DEPENDENCIES_PATH "" CACHE PATH "Path to TelPlugins dependencies" )
set ( TLP_GENERATED_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/rrplugins )
set ( TLP_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
set ( TLP_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )

# Global settings
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/bin)

# Check dependencies
if( TLP_DEPENDENCIES_PATH STREQUAL "" )
  message( FATAL_ERROR "Please set TLP_DEPENDENCIES_PATH to point to the directory containing third-party dependencies" )
elseif( NOT IS_DIRECTORY "${TLP_DEPENDENCIES_PATH}/include/Poco" )
  message( FATAL_ERROR "TLP_DEPENDENCIES_PATH is missing include/Poco" )
elseif( NOT EXISTS   "${TLP_DEPENDENCIES_PATH}/include/Poco/Poco.h" OR 
        IS_DIRECTORY "${TLP_DEPENDENCIES_PATH}/include/Poco/Poco.h" )
  message( FATAL_ERROR "Could not find Poco.h in TLP_DEPENDENCIES_PATH/include/Poco" )
elseif( NOT EXISTS   "${TLP_DEPENDENCIES_PATH}/include/Poco/Foundation.h" OR 
        IS_DIRECTORY "${TLP_DEPENDENCIES_PATH}/include/Poco/Foundation.h" )
  message( FATAL_ERROR "Could not find Foundation.h in TLP_DEPENDENCIES_PATH/include/Poco" )
endif()

# Feature selection
set ( TLP_BUILD_SHARED_LIB ON  CACHE BOOL   "Build shared library" )
set ( TLP_BUILD_STATIC_LIB ON  CACHE BOOL   "Build static library" )
set ( TLP_BUILD_APPS       ON  CACHE BOOL   "Build apps" )
set ( TLP_BUILD_EXAMPLES   OFF CACHE BOOL   "Build examples" )
set ( TLP_BUILD_TEST_TOOLS OFF CACHE BOOL   "Build test tools" )

# Dependencies

# Poco
set ( POCO_DIRECTORY "${TLP_DEPENDENCIES_PATH}" CACHE PATH "Path to directory containing Poco" )
set ( ENV{Poco_DIR} ${POCO_DIRECTORY} )
find_package ( Poco REQUIRED )

# libxml2
set( LIBXML2_PATH "${TLP_DEPENDENCIES_PATH}" )
find_package ( LibXml2 REQUIRED )

# libRoadRunner
# - Shared
set( LIBROADRUNNER_PATH "${TLP_DEPENDENCIES_PATH}" )
find_package ( LibRoadRunner REQUIRED )
# - Static
set( LIBROADRUNNERSTATIC_PATH "${TLP_DEPENDENCIES_PATH}" )
find_package ( LibRoadRunnerStatic REQUIRED )

message(STATUS "
-------------------------------------------------------------------------------
rrplugins
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

if(LIBROADRUNNER_FOUND)
    message( "  *** roadrunner libs             ${LIBROADRUNNER_LIBRARIES}")
    message( "  *** roadrunner includes         ${LIBROADRUNNER_INCLUDE_DIR}")
else()
    message( "  *** roadrunner                  *N/A")
endif()

if(LIBROADRUNNERSTATIC_FOUND)
    message( "  *** roadrunner static libs      ${LIBROADRUNNERSTATIC_LIBRARIES}")
    message( "  *** roadrunner static includes  ${LIBROADRUNNERSTATIC_INCLUDE_DIR}")
else()
    message( "  *** roadrunner static           *N/A")
endif()

if(Poco_FOUND)
    message( "  *** Poco libs                   ${Poco_LIBRARIES}")
    message( "  *** Poco includes               ${Poco_INCLUDE_DIRS}")
else()
    message( "  *** Poco                        *N/A")
endif()

if(LIBXML2_FOUND)
    message( "  *** libxml2 libs                ${LIBXML2_LIBRARIES}")
    message( "  *** libxml2 includes            ${LIBXML2_INCLUDE_DIR}")
else()
    message( "  *** libxml2                     *N/A")
endif()

# Common includes
include_directories(
  ${TLP_ROOT}
  ${TLP_ROOT}/manager
  ${Poco_INCLUDE_DIRS}
)

if(UNIX)
  find_package(Threads REQUIRED)
  set(RRPLUGINS_COMMON_SHARED_LIBS ${LIBROADRUNNER_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} dl)
else()
  if(${MSVC})
    set(RRPLUGINS_COMMON_SHARED_LIBS ${LIBROADRUNNER_LIBRARIES})
  else()
    set(RRPLUGINS_COMMON_SHARED_LIBS ${LIBROADRUNNER_LIBRARIES} iphlpapi)
  endif()
endif()

# Flags
if( MSVC )
  add_definitions(
    -DPOCO_NO_AUTOMATIC_LIBS
    -DCRT_NONSTDC_NO_DEPRECATE
    -D_CRT_SECURE_NO_WARNINGS      # MS wanting you to change basically all standard C functions :(
    )
      
  #  4251 About exporting std classes
  #  4018 Comparing unsigned/signed ints
  #  4996 Deprecated functions   
  add_definitions( "/wd4251 /wd4018 /wd4996 /nologo" )   

  set (CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS} /EHsc ")
  set (CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS} ") #/FORCE:MULTIPLE")
endif()

add_subdirectory(rrplugins)
add_subdirectory(plugins)
add_subdirectory(scripts)
add_subdirectory(wrappers)

if(TLP_BUILD_APPS)
    add_subdirectory(apps)
endif()

if(TLP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(TLP_BUILD_TEST_TOOLS)
  add_subdirectory(testing)
endif()


#======================= INSTALL STUFF ============================
# Install the "installer". Can make this more elegant later on
FILE (GLOB installerFiles installer/windows/*.*)
install ( FILES ${installerFiles} DESTINATION ./installer/windows )

# Install createPythonReleaseScript
# install ( FILES scripts/createPythonRelease.sh DESTINATION ./../ )

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

