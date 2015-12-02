cmake_minimum_required(VERSION 2.8)
set(target tel_nelder_mead)

include_directories(
../source
../../source
../../wrappers/C
${THIRD_PARTY_INSTALL_FOLDER}/include
${THIRD_PARTY_INSTALL_FOLDER}/include/c_api
${CMAKE_INSTALL_PREFIX}/include
)

link_directories(
${CMAKE_INSTALL_PREFIX}/lib
)

set(sources
nelder_mead_doc.cpp
nmWorker.cpp
nmUtils.cpp
nmObjectiveFunction.cpp
nmNelderMead.cpp
lib/nmsimplex2.cpp
nelder_mead_doc.h
nmWorker.h
nmUtils.h
nmObjectiveFunction.h
nmNelderMead.h
)

add_definitions(
-DPOCO_STATIC
-DLIBSBML_STATIC
-DEXPORT_TEL_PLUGIN
-DSTATIC_LIBSTRUCT

)

add_library(${target} MODULE ${sources})

target_link_libraries (${target}
roadrunner
telplugins_common
telplugins_core
lmfit-static
telplugins_c_api                 
roadrunner_c_api
blas
lapack
rr-libstruct-static
)

if(UNIX) 
    if(APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
    else()
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
    endif()

    set_property(TARGET ${target}
        PROPERTY  COMPILE_DEFINITIONS
        LIBSBML_STATIC
        LIBLAX_STATIC
        STATIC_PUGI
        STATIC_LIBSTRUCT
        )

endif()

if(${TLP_BUILD_EXAMPLES})
add_subdirectory(Examples)
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)
