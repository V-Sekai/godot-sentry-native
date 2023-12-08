#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sentry::breakpad_client" for configuration "RelWithDebInfo"
set_property(TARGET sentry::breakpad_client APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(sentry::breakpad_client PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libbreakpad_client.a"
  )

list(APPEND _cmake_import_check_targets sentry::breakpad_client )
list(APPEND _cmake_import_check_files_for_sentry::breakpad_client "${_IMPORT_PREFIX}/lib/libbreakpad_client.a" )

# Import target "sentry::sentry" for configuration "RelWithDebInfo"
set_property(TARGET sentry::sentry APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(sentry::sentry PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libsentry.a"
  )

list(APPEND _cmake_import_check_targets sentry::sentry )
list(APPEND _cmake_import_check_files_for_sentry::sentry "${_IMPORT_PREFIX}/lib/libsentry.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
