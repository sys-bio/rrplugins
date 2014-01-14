cmake_minimum_required(VERSION 2.8)
project(rr_plugins)

if(${RRP_BUILD_PLUGINS_API} STREQUAL ON)

OPTION (RRP_BUILD_EXAMPLES   	                "Build Plugin Examples"                     ON)

include_directories(
	../source
	../wrappers/C
)

add_subdirectory(source)
add_subdirectory(apps)
add_subdirectory(wrappers)

if(${RRP_BUILD_EXAMPLES} STREQUAL ON)
    add_subdirectory(examples)
endif()

install(
    FILES README.txt
    DESTINATION libplugins
)

endif() 


