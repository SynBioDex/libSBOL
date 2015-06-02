#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "raptor2" for configuration "Release"
set_property(TARGET raptor2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(raptor2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "C:/Users/phantom/Downloads/libxml2-2.7.8.win32/lib/libxml2.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/raptor2.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS raptor2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_raptor2 "${_IMPORT_PREFIX}/lib/raptor2.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
