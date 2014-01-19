cmake_minimum_required(VERSION 2.8)
project(plugins_examples)

#Give access to headers in the following folders
include_directories(
	${TLP_ROOT}/source
	${TLP_ROOT}/wrappers/C
 	${THIRD_PARTY_INSTALL_FOLDER}/include
 	${THIRD_PARTY_INSTALL_FOLDER}/include/rr
 	${THIRD_PARTY_INSTALL_FOLDER}/include/rr/C
)

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(python)


install(
    FILES README.txt
    DESTINATION examples
)
