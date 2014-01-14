cmake_minimum_required(VERSION 2.8)
project(rrp_c_plugin_demo C)
ENABLE_LANGUAGE (C)
set(target rrp_c_plugin_demo)

include_directories(
${RR_ROOT}/source
${RR_ROOT}/plugins/source
${RR_ROOT}/plugins/wrappers/C
${RR_ROOT}/wrappers/C
${THIRD_PARTY_INSTALL_FOLDER}/include
)

SET_SOURCE_FILES_PROPERTIES( c_plugin_demo.c PROPERTIES LANGUAGE C)
set(sources
c_plugin_demo
)

add_library(${target} MODULE ${sources})

add_definitions(
-DEXPORT_RR_PLUGIN
-DPOCO_STATIC
)


if(WIN32)
target_link_libraries (${target}
roadrunner
rrplugins_c_api
)
#else() #UNIX
#    # OSX flags:
#    #"${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
#    # OSX seems to link fine without this flag
#    if(APPLE)
#        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
#    else()
#        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
#    endif()
#
#    set_property(TARGET ${target}
#        PROPERTY  COMPILE_DEFINITIONS
#        LIBSBML_STATIC
#        LIBLAX_STATIC
#        STATIC_LIBSTRUCT
#        )
#
#    target_link_libraries ( ${target}
#        roadrunner-static
#        rr-libstruct-static
#        nleq-static
#        sbml-static
#        lapack
#        blas
#        f2c
#        pthread
#        roadrunner_c_api
#        rrplugins_c_api
#        )
endif()

#Also build the main executable
set(main_target c_plugin_demo)

include_directories(
${RR_ROOT}/source
${RR_ROOT}/plugins/source
${RR_ROOT}/plugins/wrappers/C
${RR_ROOT}/wrappers/C
${THIRD_PARTY_INSTALL_FOLDER}/include
)

set(main_sources
main.cpp
)

add_executable(${main_target} ${main_sources})

add_definitions(
-DPOCO_STATIC
)


if(WIN32)
target_link_libraries (${main_target}
roadrunner
rrplugins_c_api
)
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)

install (TARGETS ${main_target}
DESTINATION bin
COMPONENT examples
)

