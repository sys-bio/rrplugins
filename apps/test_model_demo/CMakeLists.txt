# M Totte Karlsson
# J Kyle Medley

project(test_model_demo)

include_directories(${CMAKE_SOURCE_DIR}/wrappers/C)

add_executable(test_model_demo main.c)

target_link_libraries (test_model_demo telplugins_c_api)

if(WIN32)
  add_definitions (-DWIN32)
endif()

if(UNIX)
  add_definitions (-DPOCO_STATIC)
endif()


install (TARGETS test_model_demo
  DESTINATION bin 
  COMPONENT apps
)
