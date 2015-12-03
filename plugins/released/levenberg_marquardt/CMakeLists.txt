# M Totte Karlsson
# J Kyle Medley

project( test_model )

set(RRP_LEVENBERG_MARQUARDT_SOURCES
  lm.cpp
  lmWorker.cpp
  lmUtils.cpp
  lmObjectiveFunction.cpp
  levenberg_marquardt_doc.cpp
  lm.h
  lmWorker.h
  lmUtils.h
  lmObjectiveFunction.h
  levenberg_marquardt_doc.h
)

# This is where the Levenberg lib is built
add_subdirectory(lib)

add_definitions(
  -DPOCO_STATIC
  -DLIBSBML_STATIC
  -DEXPORT_TEL_PLUGIN
  -DSTATIC_LIBSTRUCT
)

add_library(tel_levenberg_marquardt MODULE ${RRP_LEVENBERG_MARQUARDT_SOURCES})

target_link_libraries (tel_levenberg_marquardt
  telplugins_core
  ${RRPLUGINS_COMMON_SHARED_LIBS}
)

if(UNIX) 
  if(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_implicit_dylibs -undefined error")
  else()
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
  endif()

  set_property(TARGET tel_levenberg_marquardt
    PROPERTY COMPILE_DEFINITIONS
    LIBSBML_STATIC
    LIBLAX_STATIC
    STATIC_PUGI
    STATIC_LIBSTRUCT
  )
endif()

install (TARGETS tel_levenberg_marquardt
  DESTINATION plugins
  COMPONENT plugins
)
