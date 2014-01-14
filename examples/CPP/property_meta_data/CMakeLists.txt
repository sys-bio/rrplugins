cmake_minimum_required(VERSION 2.8)
set(target property_meta_data)

include_directories(
${THIRD_PARTY_INSTALL_FOLDER}/include
)

set(sources
main
)

add_library(${target} SHARED ${sources})

add_definitions(
-DPOCO_STATIC
)

if(WIN32)
target_link_libraries (${target}
roadrunner
telplugins
)
else() #UNIX
    # OSX flags:
    #"${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
    # OSX seems to link fine without this flag
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
        rr-libstruct-static
        nleq-static
        sbml-static
        lapack
        blas
        f2c
        pthread
        roadrunner_c_api
        telplugins_c_api
        )
endif()

if(${MSVC})
#set (CMAKE_SHARED_LINKER_FLAGS     "${CMAKE_SHARED_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/add_noise.def\"")
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT examples
)

