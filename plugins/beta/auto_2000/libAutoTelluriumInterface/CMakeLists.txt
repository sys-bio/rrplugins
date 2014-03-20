cmake_minimum_required(VERSION 2.8)
set(target libTelluriumAutoInterface)

include_directories(

)

link_directories(
${RRE_INSTALL_LIB_PATH}
${CMAKE_BINARY_DIR}/lib
)

#The api is built as a static library..
set(src
#telAutoData
telAutoConstants
telAutoTelluriumInterface
telAutoUtils
)

add_library(${target}-static STATIC
${src}
)

if(WIN32)
    set_property(TARGET ${target}-static 
        PROPERTY  COMPILE_DEFINITIONS 
        STATIC_AUTO
        STATIC_TEL_AUTO
        )
    
    target_link_libraries ( ${target}-static
        telplugins_common
        )
 
endif()

install(   
	TARGETS ${target}-static
	RUNTIME DESTINATION bin 
	ARCHIVE DESTINATION lib 
	LIBRARY DESTINATION lib 
	)

