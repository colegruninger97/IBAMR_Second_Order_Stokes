#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IBAMR::BUNDLED_MUPARSER" for configuration "Debug"
set_property(TARGET IBAMR::BUNDLED_MUPARSER APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(IBAMR::BUNDLED_MUPARSER PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libBUNDLED_MUPARSER.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libBUNDLED_MUPARSER.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS IBAMR::BUNDLED_MUPARSER )
list(APPEND _IMPORT_CHECK_FILES_FOR_IBAMR::BUNDLED_MUPARSER "${_IMPORT_PREFIX}/lib/libBUNDLED_MUPARSER.dylib" )

# Import target "IBAMR::IBTK2d" for configuration "Debug"
set_property(TARGET IBAMR::IBTK2d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(IBAMR::IBTK2d PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libIBTK2d.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libIBTK2d.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS IBAMR::IBTK2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_IBAMR::IBTK2d "${_IMPORT_PREFIX}/lib/libIBTK2d.dylib" )

# Import target "IBAMR::IBTK3d" for configuration "Debug"
set_property(TARGET IBAMR::IBTK3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(IBAMR::IBTK3d PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libIBTK3d.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libIBTK3d.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS IBAMR::IBTK3d )
list(APPEND _IMPORT_CHECK_FILES_FOR_IBAMR::IBTK3d "${_IMPORT_PREFIX}/lib/libIBTK3d.dylib" )

# Import target "IBAMR::IBAMR2d" for configuration "Debug"
set_property(TARGET IBAMR::IBAMR2d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(IBAMR::IBAMR2d PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libIBAMR2d.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libIBAMR2d.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS IBAMR::IBAMR2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_IBAMR::IBAMR2d "${_IMPORT_PREFIX}/lib/libIBAMR2d.dylib" )

# Import target "IBAMR::IBAMR3d" for configuration "Debug"
set_property(TARGET IBAMR::IBAMR3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(IBAMR::IBAMR3d PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libIBAMR3d.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libIBAMR3d.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS IBAMR::IBAMR3d )
list(APPEND _IMPORT_CHECK_FILES_FOR_IBAMR::IBAMR3d "${_IMPORT_PREFIX}/lib/libIBAMR3d.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
