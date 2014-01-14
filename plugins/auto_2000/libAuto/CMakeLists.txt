cmake_minimum_required(VERSION 2.8)
set(target libAuto)
include_directories(
libf2c
)
#The api is built as a shared library..
set(src
main
autlab
autlib1
autlib2
autlib3
autlib4
autlib5
#auto_api
conpar
dmatrix
eispack
getopt
reduce
setubv
vsAuto
worker
libf2c/z_log
libf2c/z_exp
libf2c/z_abs
libf2c/r_lg10
libf2c/pow_ii
libf2c/pow_di
libf2c/pow_dd
libf2c/i_nint
libf2c/i_dnnt
libf2c/d_sign
libf2c/d_lg10
libf2c/d_imag
libf2c/cabs

)

##------- SHARED TARGET
#add_library(${target} SHARED
#${src}
#)
#
#if(WIN32)
#    set_property(TARGET ${target} 
#        PROPERTY  COMPILE_DEFINITIONS 
#        EXPORT_AUTO
#        )
#    
#endif()
#----------------------

#------- STATIC target
add_library(${target}-static STATIC
${src}
)

if(WIN32)
    set_property(TARGET ${target}-static 
        PROPERTY  COMPILE_DEFINITIONS 
        STATIC_AUTO
        )
    
endif()

#Don't install anything. link statically to the plugin
##=============== INSTALL =====================
install(
	FILES 
    vsAuto.h 
    libf2c/auto_f2c.h
    auto_exporter.h				 					
	DESTINATION include/auto_api 
	)

install(   
	TARGETS ${target}-static
	RUNTIME DESTINATION bin 
	ARCHIVE DESTINATION lib 
	LIBRARY DESTINATION lib 
	)

