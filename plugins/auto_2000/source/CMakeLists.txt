cmake_minimum_required(VERSION 2.8)

set(target rrp_auto2000)

include_directories(
../../source   #RoadRunner Sources
../../../source   #RoadRunner Sources
../../wrappers/C
${CMAKE_INSTALL_PREFIX}/include
${THIRD_PARTY_INSTALL_FOLDER}/include
)

link_directories (
${CMAKE_BINARY_DIR}/lib
${CMAKE_INSTALL_PREFIX}/lib
)

set(sources
rrAutoPlugin
rrAutoWorker
)


add_definitions(
-DEXPORT_RR_PLUGIN
-DPOCO_STATIC
-DLIBSBML_STATIC
-DSTATIC_AUTO
-DSTATIC_RR_AUTO
-DSTATIC_LIBSTRUCT
-DLIBLAX_STATIC
-DSTATIC_NLEQ
)

add_library(${target} MODULE ${sources})

if(WIN32)
if(${BORLAND})
    set (CMAKE_CXX_FLAGS   "${CMAKE_MODULE_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/rrp_auto2000.def\"")
message(${CMAKE_MODULE_LINKER_FLAGS} )    
endif()


target_link_libraries (${target}
roadrunner
rrplugins
rrAutoInterface-static
libAuto-static
)
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)

