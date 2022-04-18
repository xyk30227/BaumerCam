#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "bgapi::bgapi2_ext_sc" for configuration "Release"
set_property(TARGET bgapi::bgapi2_ext_sc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(bgapi::bgapi2_ext_sc PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/bgapi2_ext_sc.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "bgapi::bgapi2_genicam"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/bgapi2_ext_sc.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS bgapi::bgapi2_ext_sc )
list(APPEND _IMPORT_CHECK_FILES_FOR_bgapi::bgapi2_ext_sc "${_IMPORT_PREFIX}/lib/bgapi2_ext_sc.lib" "${_IMPORT_PREFIX}/bin/bgapi2_ext_sc.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
