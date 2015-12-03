# M Totte Karlsson
# J Kyle Medley

#The C-api is built as a shared library..
add_library(telplugins_c_api SHARED
  telplugins_c_api
  telplugins_properties_api
  telplugins_telluriumdata_api
  telplugins_matrix_api
  telplugins_cpp_support
  telplugins_utilities
  telAPIHandleManager
)

target_link_libraries ( telplugins_c_api
  telplugins_core
  telplugins_common
  telplugins_math
  ${RRPLUGINS_COMMON_SHARED_LIBS}
)

#Link C_api shared lib statically to roadrunner and libsbml
if(WIN32)
  set_property(TARGET telplugins_c_api
    PROPERTY  COMPILE_DEFINITIONS
    EXPORT_RRP
    LIBSBML_STATIC
    LIBLAX_STATIC
    POCO_STATIC
    STATIC_LIBSTRUCT
  )
else() 
  if(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
  else()
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
  endif()
  
  set_property(TARGET telplugins_c_api
    PROPERTY  COMPILE_DEFINITIONS
    LIBSBML_STATIC
    LIBLAX_STATIC
    STATIC_PUGI
    STATIC_LIBSTRUCT
  )
endif()

if(TLP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(TLP_BUILD_TESTS)
    add_subdirectory(Testing)
endif()

install(
  TARGETS telplugins_c_api
  RUNTIME DESTINATION bin COMPONENT pluginsLib
  ARCHIVE DESTINATION lib COMPONENT pluginsLib
  LIBRARY DESTINATION lib COMPONENT pluginsLib
)

