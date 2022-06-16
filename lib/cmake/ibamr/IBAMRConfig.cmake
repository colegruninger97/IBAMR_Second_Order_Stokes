## ---------------------------------------------------------------------
##
## Copyright (c) 2020 - 2021 by the IBAMR developers
## All rights reserved.
##
## This file is part of IBAMR.
##
## IBAMR is free software and is distributed under the 3-clause BSD
## license. The full text of the license can be found in the file
## COPYRIGHT at the top level directory of IBAMR.
##
## ---------------------------------------------------------------------

# This file is a template that is populated by CMake with the actual locations
# of external dependencies and also the file containing information on IBAMR's
# own targets.

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was IBAMRConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# Don't set compiler flags, but save them
SET(IBAMR_C_FLAGS "")
SET(IBAMR_CXX_FLAGS " -Wno-undefined-var-template -Wno-unneeded-internal-declaration")
SET(IBAMR_Fortran_FLAGS "")

SET(MPI_ROOT "")
FIND_PACKAGE(MPI REQUIRED)

IF(NOT FALSE)
  SET(Boost_ROOT "/usr/local/")
  IF(ON)
    SET(Boost_NO_SYSTEM_PATHS ON)
    # Modern versions of Boost install some extra files which we want to ignore
    # since they are incompatible with Boost_NO_SYSTEM_PATHS. If we don't set
    # this then CMake will set us up with a system copy of boost even when
    # Boost_ROOT is something else
    #
    # This was fixed in CMake in 3.19: see
    # https://gitlab.kitware.com/cmake/cmake/-/issues/21200
    IF(${CMAKE_VERSION} VERSION_LESS "3.19.0")
      SET(Boost_NO_BOOST_CMAKE ON)
    ENDIF()
  ENDIF()
  FIND_PACKAGE(Boost 1.57 REQUIRED)

  # We do not want to set BOOST_ALL_NO_LIB in case IBAMR is linked to other
  # libraries that *do* link against boost libraries
  GET_TARGET_PROPERTY(_boost_definitions Boost::headers
    INTERFACE_COMPILE_DEFINITIONS)
  # Deal with both cases of _boost_definitions not being found
  IF(NOT "${_boost_definitions}" STREQUAL "_boost_definitions-NOTFOUND" AND
     NOT "${_boost_definitions}" STREQUAL "")
    LIST(REMOVE_ITEM _boost_definitions "BOOST_ALL_NO_LIB")
    SET_TARGET_PROPERTIES(Boost::headers PROPERTIES INTERFACE_COMPILE_DEFINITIONS
      "${_boost_definitions}")
  ENDIF()
ENDIF()

IF(NOT FALSE)
  SET(Eigen3_ROOT "")
  FIND_PACKAGE(Eigen3 3.2.5 REQUIRED)
ENDIF()

# non-bundled muParser is not handled as a package so we don't set it up again
# here

# Our linkage with SILO is purely internal and none of our headers include
# silo.h so we do not handle it as an externally-facing dependency here.

SET(HDF5_ROOT "/usr/local/")
FIND_PACKAGE(HDF5 REQUIRED)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/IBAMRTargets.cmake)

# Attempt to avoid conflicts between potential system copies of bundled
# dependencies and the actual bundled dependencies by putting their include
# directories at the front:

IF(FALSE)
  GET_TARGET_PROPERTY(_boost_includes IBAMR::BUNDLED_BOOST
    INTERFACE_INCLUDE_DIRECTORIES)
  TARGET_INCLUDE_DIRECTORIES(IBAMR::IBTK2d BEFORE INTERFACE "${_boost_includes}")
  TARGET_INCLUDE_DIRECTORIES(IBAMR::IBTK3d BEFORE INTERFACE "${_boost_includes}")
ENDIF()

IF(FALSE)
  GET_TARGET_PROPERTY(_eigen3_includes IBAMR::BUNDLED_EIGEN3
    INTERFACE_INCLUDE_DIRECTORIES)
  TARGET_INCLUDE_DIRECTORIES(IBAMR::IBTK2d BEFORE INTERFACE "${_eigen3_includes}")
  TARGET_INCLUDE_DIRECTORIES(IBAMR::IBTK3d BEFORE INTERFACE "${_eigen3_includes}")
ENDIF()

IF(TRUE)
  GET_TARGET_PROPERTY(_muparser_includes IBAMR::BUNDLED_MUPARSER
    INTERFACE_INCLUDE_DIRECTORIES)
  TARGET_INCLUDE_DIRECTORIES(IBAMR::IBTK2d BEFORE INTERFACE "${_muparser_includes}")
  TARGET_INCLUDE_DIRECTORIES(IBAMR::IBTK3d BEFORE INTERFACE "${_muparser_includes}")
ENDIF()
