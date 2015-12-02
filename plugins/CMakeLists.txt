cmake_minimum_required(VERSION 3.2)
project(plugins)

#Give all plugins access to headers in the following folders
include_directories(
  ${TLP_ROOT}/rrplugins/core
  ${TLP_ROOT}/rrplugins/common
  ${TLP_ROOT}/rrplugins/math
  ${TLP_ROOT}/wrappers/C
  ${THIRD_PARTY_INSTALL_FOLDER}/include
)

set ( TLP_BUILD_BETA_PLUGINS ON CACHE BOOL "Build plugins currently in a beta development state" )

if(${TLP_BUILD_BETA_PLUGINS} STREQUAL ON)
  add_subdirectory(beta)
endif()

add_subdirectory(released)

install(
  FILES README.txt
  DESTINATION plugins
)
