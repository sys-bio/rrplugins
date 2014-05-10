cmake_minimum_required(VERSION 2.8)
set(target plugin_info)

add_executable(${target} 
main.cpp 
)

target_link_libraries (${target} 
telplugins_core
)

if(WIN32)
add_definitions(
-DWIN32
)

endif()

if(UNIX)
add_definitions(
-DPOCO_STATIC
)
endif()


install (TARGETS ${target} 		
DESTINATION bin 
COMPONENT apps
)
