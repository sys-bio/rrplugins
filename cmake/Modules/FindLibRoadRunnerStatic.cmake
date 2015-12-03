#.rst:
# FindLibRoadRunnerStatic
# -----------
#
# Try to find libRoadRunner, an SBML-compliant simulation library.
# Find static versions of libs.
# Set LIBROADRUNNER_STATIC_PATH to give a hint about where to search.
#
# Once done this will define
#
# ::
#
#   LIBROADRUNNER_STATIC_FOUND - System has libRoadRunner static libs
#   LIBROADRUNNER_STATIC_INCLUDE_DIR - The libRoadRunner include directory
#   LIBROADRUNNER_STATIC_LIBRARIES - The libraries needed to use libRoadRunner
#   LIBROADRUNNER_STATIC_DEFINITIONS - Compiler switches required for using libRoadRunner
#   LIBROADRUNNER_STATIC_VERSION_STRING - the version of libRoadRunner found

#=============================================================================
# Copyright 2015 J. Kyle Medley
#
# Licensed under the Apache License, Version 2.0
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#
# Based on FindLibXml2.cmake
#
#=============================================================================

# find version info file
find_file(LIBROADRUNNER_STATIC_VERSION_FILE NAME "VERSION.txt"
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}
  )

if(LIBROADRUNNER_STATIC_VERSION_FILE AND EXISTS "${LIBROADRUNNER_STATIC_VERSION_FILE}" AND NOT IS_DIRECTORY ${LIBROADRUNNER_STATIC_VERSION_FILE})
  file(STRINGS "${LIBROADRUNNER_STATIC_VERSION_FILE}" LIBROADRUNNER_STATIC_VERSION_STRING
      REGEX "^[0-9]+.[0-9]+.[0-9]+")
endif()

# include dirs
find_path(LIBROADRUNNER_STATIC_INCLUDE_DIR NAMES rrRoadRunner.h
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/include/rr
  )

# libraries
find_library(LIBROADRUNNER_STATIC_LIBRARY NAMES roadrunner-static
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(SUNDIALS_CVODE_LIBRARY NAMES sundials_cvode
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(SUNDIALS_NVECSERIAL_LIBRARY NAMES sundials_nvecserial
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(F2C_LIBRARY NAMES f2c
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(BLAS_LIBRARY NAMES blas
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(LAPACK_LIBRARY NAMES lapack
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(NLEQ_LIBRARY_STATIC NAMES nleq-static
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(RR_LIBSTRUCT_LIBRARY_STATIC NAMES rr-libstruct-static
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(POCO_FOUNDATION_LIBRARY_STATIC NAMES PocoFoundation
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

find_library(SBML_LIBRARY NAMES sbml
  HINTS
  ${LIBROADRUNNER_STATIC_PATH}/lib
  )

set ( LIBROADRUNNER_STATIC_LIBRARIES ${LIBROADRUNNER_STATIC_LIBRARY} ${SUNDIALS_CVODE_LIBRARY}
      ${SUNDIALS_NVECSERIAL_LIBRARY} ${F2C_LIBRARY} ${BLAS_LIBRARY} ${LAPACK_LIBRARY} 
      ${NLEQ_LIBRARY_STATIC} ${RR_LIBSTRUCT_LIBRARY_STATIC} 
      ${POCO_FOUNDATION_LIBRARY_STATIC} ${SBML_LIBRARY} )
message( STATUS ${LIBROADRUNNER_STATIC_LIBRARIES} )
  
# handle the QUIETLY and REQUIRED arguments and set LIBROADRUNNER_STATIC_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibRoadRunnerStatic
                                  REQUIRED_VARS LIBROADRUNNER_STATIC_LIBRARIES LIBROADRUNNER_STATIC_INCLUDE_DIR
                                  VERSION_VAR LIBROADRUNNER_STATIC_VERSION_STRING)

mark_as_advanced(LIBROADRUNNER_STATIC_INCLUDE_DIR LIBROADRUNNER_STATIC_LIBRARIES)
