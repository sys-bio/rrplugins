CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(rrplugins_c-api)
set(target rrplugins_c_api)

include_directories(${RR_GENERATED_HEADER_PATH}) #we have to do this to get the generated header

include_directories(
${RR_ROOT}/source
${RR_ROOT}/libplugins/source
${THIRD_PARTY_INSTALL_FOLDER}/include
)

#The C-api is built as a shared library..
add_library(${target} SHARED
rrplugins_c_api
rrplugins_cpp_support
rrplugins_properties_api
)

if(${BORLAND})
    set (CMAKE_SHARED_LINKER_FLAGS     "${CMAKE_SHARED_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/rrplugins_c_api.def\"")
endif()

#Link C_api dll statically to roadrunner and libsbml
if(WIN32)
    set_property(TARGET ${target}
        PROPERTY  COMPILE_DEFINITIONS
        EXPORT_RRP
        LIBSBML_STATIC
        LIBLAX_STATIC
        POCO_STATIC
        STATIC_LIBSTRUCT
        )

    target_link_libraries ( ${target}
        roadrunner_c_api
        roadrunner
        rrplugins
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
        roadrunner_c_api
        roadrunner-static
        rrplugins_api
        rr-libstruct-static
        nleq-static
        sbml-static
        lapack
        blas
        f2c
        pthread
        )
endif()

if(RRP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(RRP_BUILD_TESTS)
    add_subdirectory(Testing)
endif()

#=============== INSTALL =====================
#=== HEADERS
FILE (GLOB headers rrp*.h)
install (   
    FILES ${headers}
    DESTINATION include/libplugins
    COMPONENT pluginsLib
    )

install(
    TARGETS ${target}
    RUNTIME DESTINATION bin COMPONENT pluginsLib
    ARCHIVE DESTINATION lib COMPONENT pluginsLib
    LIBRARY DESTINATION lib COMPONENT pluginsLib
)

