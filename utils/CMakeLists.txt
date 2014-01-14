CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(telutils)

set(target telutils)

include_directories(
    ${TLP_ROOT}/source
    ${THIRD_PARTY_INSTALL_FOLDER}/include
    ${THIRD_PARTY_INSTALL_FOLDER}/include/libxml2
    )

set(sources
telArrayList
telStringBuilder
telStringList
telStringListContainer
telStringUtils
telUtils
)

#SHARED VERSION ----------------
add_library(${target} SHARED ${sources})

set_property(TARGET ${target}
PROPERTY  COMPILE_DEFINITIONS
EXPORT_TLP_UTIL_API
POCO_NO_AUTOMATIC_LIBS
)

#libraries to link with our shared lib
if(UNIX)
    set(staticLibExt ".a")
else()
    set(staticLibExt "")
endif(UNIX)

target_link_libraries (${target}
    )

if(${MSVC})
    target_link_libraries (${target}
        iphlpapi)
endif()

if(UNIX)
    target_link_libraries (${target}
        pthread
        sbml
        dl
        f2c${staticLibExt}
        )
else()
    target_link_libraries (${target}
        )
endif(UNIX)

install(TARGETS ${target}
        RUNTIME DESTINATION bin COMPONENT core
        LIBRARY DESTINATION lib COMPONENT core
        ARCHIVE DESTINATION lib COMPONENT core
)
#END OF SHARED VERSION ----------------

#STATIC VERSION
add_library(${target}-static STATIC ${sources})

set_property(TARGET ${target}-static
    PROPERTY COMPILE_DEFINITIONS
    STATIC_TLP_UTIL_API
    POCO_STATIC
    POCO_NO_AUTOMATIC_LIBS
    )

#libraries to link with static lib
target_link_libraries (${target}-static
    )

if(WIN32)
    target_link_libraries (${target}-static
        )
endif(WIN32)

if(UNIX)
    target_link_libraries (${target}-static
        )
endif(UNIX)

#Libxml we can't build right now
if(${BORLAND})
    target_link_libraries (${target}-static
        )
endif()

if(${MSVC})
    target_link_libraries(${target}-static 
    ) 
    #Disable some VS Warnings 
    #           4251 About exporting std classes
    #           4018 Comparing unsigned/signed ints
    #           4996 Deprecated functions   
add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4251 /wd4018 /wd4996 /nologo" )

endif()

#--- INSTALL STUFF
install(TARGETS ${target}-static
    LIBRARY DESTINATION lib COMPONENT core
    ARCHIVE DESTINATION lib COMPONENT core
    )

#=== HEADERS
FILE (GLOB headers tel*.h)
install (   
    FILES ${headers}
    DESTINATION include
    COMPONENT core
    )

