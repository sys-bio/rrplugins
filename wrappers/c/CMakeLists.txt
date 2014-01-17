CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(telplugins_c-api)
set(target telplugins_c_api)

include_directories(${RR_GENERATED_HEADER_PATH}) #we have to do this to get the generated header

include_directories(
${TLP_ROOT}/source
${THIRD_PARTY_INSTALL_FOLDER}/include
)
link_directories(
${THIRD_PARTY_INSTALL_FOLDER}/lib
)


#The C-api is built as a shared library..
add_library(${target} SHARED
telplugins_c_api
telplugins_cpp_support
telplugins_properties_api
telplugins_utilities
telplugins_roadrunnerdata_api
)

if(${BORLAND})
    set (CMAKE_SHARED_LINKER_FLAGS     "${CMAKE_SHARED_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/telplugins_c_api.def\"")
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
        #roadrunner_c_api
        roadrunner
        telplugins
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
        #roadrunner_c_api
        roadrunner-static
        telplugins_api
        rr-libstruct-static
        nleq-static
        sbml-static
        lapack
        blas
        f2c
        pthread
        )
endif()

if(TLP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(TLP_BUILD_TESTS)
    add_subdirectory(Testing)
endif()

#=============== INSTALL =====================
#=== HEADERS
FILE (GLOB headers rrp*.h)
install (   
    FILES ${headers}
    DESTINATION include/telplugins
    COMPONENT pluginsLib
    )

install(
    TARGETS ${target}
    RUNTIME DESTINATION bin COMPONENT pluginsLib
    ARCHIVE DESTINATION lib COMPONENT pluginsLib
    LIBRARY DESTINATION lib COMPONENT pluginsLib
)

