cmake_minimum_required(VERSION 2.8)

link_directories(
${CMAKE_BINARY_DIR}/lib
)

add_subdirectory(libAuto)
add_subdirectory(libAutoTelluriumInterface)
add_subdirectory(source)

if(${TLP_BUILD_EXAMPLES})
add_subdirectory(examples)
endif()


