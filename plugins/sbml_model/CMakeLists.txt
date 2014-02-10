cmake_minimum_required(VERSION 2.8)
set(target tel_sbml_model)

set(sources
SBMLModel
sbml_model_doc
)

add_library(${target} MODULE ${sources})

add_definitions(
-DEXPORT_RR_PLUGIN
-DPOCO_STATIC
)

if(WIN32)
target_link_libraries (${target}
roadrunner
telplugins
)
else() #UNIX
    if(APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
    else()
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
    endif()

    set_property(TARGET ${target}
        PROPERTY  COMPILE_DEFINITIONS
        )

    target_link_libraries ( ${target}
        )
endif()

if(${MSVC})
#set (CMAKE_SHARED_LINKER_FLAGS     "${CMAKE_SHARED_LINKER_FLAGS} \"/DEF:${CMAKE_CURRENT_SOURCE_DIR}/add_noise.def\"")
endif()

install (TARGETS ${target}
DESTINATION plugins
COMPONENT plugins
)

install(FILES
sbml_test_0001.xml
DESTINATION plugins
)


