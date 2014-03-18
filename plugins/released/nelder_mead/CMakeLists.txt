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
nelder_mead_doc
nmWorker
nmUtils
nmObjectiveFunction
nmNelderMead
lib/nmsimplex2
)

add_definitions(
-DPOCO_STATIC
-DLIBSBML_STATIC
-DEXPORT_TEL_PLUGIN
-DSTATIC_LIBSTRUCT

)

add_library(${target} MODULE ${sources})

if(WIN32)
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

else() 
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

    target_link_libraries ( ${target}
        roadrunner-static
        lmfit-static
        #roadrunner_c_api
        telplugins_api-static
        )
endif()

if(${INSTALL_EXAMPLES})
add_subdirectory(Examples)
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)
