CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(telplugins)

set(sources
telArrayList.cpp
telArrayedParameter.cpp
telConstants.cpp
telException.cpp
telFileName.cpp
telIniFile.cpp
telIniKey.cpp
telIniSection.cpp
telLogger.cpp
telProperties.cpp
telPropertyBase.cpp
telStringBuilder.cpp
telStringList.cpp
telStringListContainer.cpp
telStringUtils.cpp
telTelluriumData.cpp
telUtils.cpp
telArrayList.h
telArrayedParameter.h
telConstants.h
telException.h
telFileName.h
telIniFile.h
telIniKey.h
telIniSection.h
telLogger.h
telProperties.h
telPropertyBase.h
telStringBuilder.h
telStringList.h
telStringListContainer.h
telStringUtils.h
telTelluriumData.h
telUtils.h
)

# ** Shared lib ******
add_library(telplugins_common SHARED ${sources})

set_property(TARGET telplugins_common
  PROPERTY  COMPILE_DEFINITIONS
  EXPORT_COMMON_API
  LIBSBML_USE_CPP_NAMESPACE
  LIBSBML_STATIC
  LIBLAX_STATIC
  STATIC_LIBSTRUCT
  STATIC_NLEQ
  POCO_STATIC
  POCO_NO_AUTOMATIC_LIBS
)

target_link_libraries (telplugins_common
  roadrunner
  sundials_cvode
  sundials_nvecserial
  blas
  lapack
  nleq-static
  rr-libstruct-static
  poco_foundation-static
  )

if(UNIX)
    target_link_libraries(telplugins_common xml2)
elseif(${WIN32})
    target_link_libraries (telplugins_common libxml2)
elseif(${BORLAND})
    target_link_libraries (telplugins_common libxml2_xe)
endif()

if(${MSVC})
    target_link_libraries (telplugins_common
        iphlpapi)
endif()

if(UNIX)
    target_link_libraries (telplugins_common
        pthread
        sbml
        dl
        f2c${staticLibExt}
        )
else()
    target_link_libraries (telplugins_common
        libf2c
        libsbml-static
        )
endif(UNIX)

install(TARGETS telplugins_common
        RUNTIME DESTINATION bin COMPONENT pluginsLib
        LIBRARY DESTINATION lib COMPONENT pluginsLib
        ARCHIVE DESTINATION lib COMPONENT pluginsLib
)

#END OF SHARED VERSION ----------------

#STATIC VERSION
add_library(telplugins_common-static STATIC ${sources})

set_property(TARGET telplugins_common-static
    PROPERTY COMPILE_DEFINITIONS
    STATIC_PLUGIN_API
    LIBSBML_USE_CPP_NAMESPACE
    LIBSBML_STATIC
    LIBLAX_STATIC
    STATIC_LIBSTRUCT
    STATIC_NLEQ
    POCO_STATIC
    POCO_NO_AUTOMATIC_LIBS
    )

#libraries to link with static lib
target_link_libraries (telplugins_common-static
    sundials_cvode
    sundials_nvecserial
    blas
    lapack
    nleq-static
    rr-libstruct-static
    poco_foundation-static
    )

if(WIN32)
    target_link_libraries (telplugins_common-static
        libsbml-static
        libf2c
        iphlpapi
	libxml2
        )
endif(WIN32)

if(UNIX)
    target_link_libraries (telplugins_common-static
        sbml-static
        f2c
        xml2
        dl
        pthread
        )
endif(UNIX)

#Libxml we can't build right now
if(${BORLAND})
    target_link_libraries (telplugins_common-static
        libxml2_xe
        )
endif()

if(${MSVC})
    #Disable some VS Warnings 
    #           4251 About exporting std classes
    #           4018 Comparing unsigned/signed ints
    #           4996 Deprecated functions   
add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4251 /wd4018 /wd4996 /nologo" )

endif()

if(BUILD_TESTS)
    add_subdirectory(testing)
endif()

#--- INSTALL STUFF
install(TARGETS telplugins_common-static
    LIBRARY DESTINATION lib COMPONENT pluginsLib
    ARCHIVE DESTINATION lib COMPONENT pluginsLib
    )

#=== HEADERS
FILE (GLOB headers rr*.h)
install (   
    FILES ${headers}
    DESTINATION include/telplugins
    COMPONENT pluginsLib
    )

