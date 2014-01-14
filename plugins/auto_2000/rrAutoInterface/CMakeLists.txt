cmake_minimum_required(VERSION 2.8)
set(target rrAutoInterface)

include_directories(
../../source        #Plugin lib source
../../../source     #RoadRunner lib source

)

link_directories(
${RRE_INSTALL_LIB_PATH}
${CMAKE_BINARY_DIR}/lib
)

#The api is built as a static library..
set(src
rrAutoData
rrAutoInputConstants
rrRRAuto
rrRRAutoSetupControl
)

add_library(${target}-static STATIC
${src}
)

if(WIN32)
    set_property(TARGET ${target}-static 
        PROPERTY  COMPILE_DEFINITIONS 
        STATIC_AUTO
        STATIC_RR_AUTO
        STATIC_PLUGIN_API
        )
    
    target_link_libraries ( ${target}-static
#        libAuto-static
#        roadrunner
#        rrplugins_api-static
#        poco_foundation-static
#        IPHLPAPI
        )
 
endif()

install(   
	TARGETS ${target}-static
	RUNTIME DESTINATION bin 
	ARCHIVE DESTINATION lib 
	LIBRARY DESTINATION lib 
	)

