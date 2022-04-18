#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "bgapi::bgapi2_genicam" for configuration "Release"
set_property(TARGET bgapi::bgapi2_genicam APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(bgapi::bgapi2_genicam PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/bgapi2_genicam.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/bgapi2_genicam.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS bgapi::bgapi2_genicam )
list(APPEND _IMPORT_CHECK_FILES_FOR_bgapi::bgapi2_genicam "${_IMPORT_PREFIX}/lib/bgapi2_genicam.lib" "${_IMPORT_PREFIX}/bin/bgapi2_genicam.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
