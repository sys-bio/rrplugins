# M Totte Karlsson
# J Kyle Medley

set(target tel_auto2000)

add_subdirectory(libAuto)
add_subdirectory(libAutoTelluriumInterface)

if (TLP_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Auto2k lib includes
include_directories(libAutoTelluriumInterface)

set(RRP_AUTO2000_SOURCES
  telAutoPlugin.cpp
  telAutoWorker.cpp
  telAutoDataParser.cpp
  auto_utils.cpp
  auto2000_doc.cpp
  telAutoPlugin.h
  telAutoWorker.h
  telAutoDataParser.h
  auto_utils.h
  auto2000_doc.h
)

add_definitions(
  -DEXPORT_TEL_PLUGIN
  -DPOCO_STATIC
  -DLIBSBML_STATIC
  -DSTATIC_AUTO
  -DSTATIC_TEL_AUTO
  -DSTATIC_LIBSTRUCT
  -DLIBLAX_STATIC
  -DSTATIC_NLEQ
)

add_library(tel_auto2000 MODULE ${RRP_AUTO2000_SOURCES})

target_link_libraries (tel_auto2000
  telplugins_core
  ${RRPLUGINS_COMMON_SHARED_LIBS}
)

install (TARGETS tel_auto2000
  DESTINATION plugins
  COMPONENT plugins
)

