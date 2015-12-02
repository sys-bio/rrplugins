cmake_minimum_required(VERSION 2.8)
project(tellurium)

include_directories(
  ${TLP_ROOT}/source/core
  ${TLP_ROOT}/source/common
  ${THIRD_PARTY_INSTALL_FOLDER}/include
  ${THIRD_PARTY_INSTALL_FOLDER}/include/rr # deprecated
  ${THIRD_PARTY_INSTALL_FOLDER}/include/roadrunner
  ${THIRD_PARTY_INSTALL_FOLDER}/include/sbml
  ${THIRD_PARTY_INSTALL_FOLDER}/include/cvode
  ${THIRD_PARTY_INSTALL_FOLDER}/include/clapack
)

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(math)

