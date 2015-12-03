# M Totte Karlsson
# J Kyle Medley

project( rrplugins_python_api )

#=============== INSTALL =====================

FILE (GLOB pyFiles tel*.py)

install(
  FILES
  ${pyFiles}
  __init__.py
  README.txt
  DESTINATION site-packages/teplugins
  COMPONENT telplugins
)


