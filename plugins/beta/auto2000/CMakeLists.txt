cmake_minimum_required(VERSION 2.8)
set(target tel_auto2000)

add_subdirectory(libAuto)
add_subdirectory(libAutoTelluriumInterface)

if(${TLP_BUILD_EXAMPLES})
add_subdirectory(examples)
endif()

include_directories(
../../source   #RoadRunner Sources
../../../source   #RoadRunner Sources
../../wrappers/C
../libAutoTelluriumInterface
${CMAKE_INSTALL_PREFIX}/include
${THIRD_PARTY_INSTALL_FOLDER}/include
)

link_directories (
${CMAKE_BINARY_DIR}/lib
${CMAKE_INSTALL_PREFIX}/lib
)

set(sources
telAutoPlugin
telAutoWorker
telAutoDataParser
auto_utils
auto2000_doc
)

add_definitions(
-DEXPORT_TEL_PLUGIN
-DPOCO_STATIC
-DLIBSBML_STATIC
-DSTATIC_AUTO
-DSTATIC_TEL_AUTO
-DSTATIC_LIBSTRUCT
-DLIBLAX_STATIC
-DSTATIC_NLEQ
)

add_library(${target} MODULE ${sources})

if(WIN32)
if(${BORLAND})
    set (CMAKE_CXX_FLAGS   "${CMAKE_MODULE_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/tel_auto2000.def\"")
message(${CMAKE_MODULE_LINKER_FLAGS} )    
endif()


target_link_libraries (${target}
roadrunner
telplugins_core
telplugins_common
libTelluriumAutoInterface-static
libAuto-static
)
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)

