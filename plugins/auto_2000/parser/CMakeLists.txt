cmake_minimum_required(VERSION 2.8)

set(target rrp_auto2000)

include_directories(
../../source
../../wrappers/C
${CMAKE_INSTALL_PREFIX}/include
)

link_directories (
${CMAKE_BINARY_DIR}/lib
${CMAKE_INSTALL_PREFIX}/lib
)

set(sources
rrAutoPlugin
rrAutoThread
)


add_definitions(
-DPOCO_STATIC
-DLIBSBML_STATIC
-DSTATIC_RR
-DSTATIC_RRE
-DSTATIC_PLUGIN_API
-DSTATIC_AUTO
-DSTATIC_RR_AUTO
-DSTATIC_LIBSTRUCT
-DLIBLAX_STATIC
-DSTATIC_NLEQ
-DEXPORT_PLUGIN
)

add_library(${target} SHARED
${sources}
)

if(WIN32)
add_definitions( -DEXPORT_RR_PLUGIN)

target_link_libraries (${target}
roadrunner-static
rrplugins_api-static
rrAutoInterface-static
libAuto-static
poco_foundation-static
libsbml-static
libxml2
rr-libstruct-static
sundials_cvode
sundials_nvecserial
blas
lapack
libf2c
nleq-static
 
)
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)

