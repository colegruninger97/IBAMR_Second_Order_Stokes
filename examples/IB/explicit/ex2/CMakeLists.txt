## ---------------------------------------------------------------------
##
## Copyright (c) 2020 - 2020 by the IBAMR developers
## All rights reserved.
##
## This file is part of IBAMR.
##
## IBAMR is free software and is distributed under the 3-clause BSD
## license. The full text of the license can be found in the file
## COPYRIGHT at the top level directory of IBAMR.
##
## ---------------------------------------------------------------------

IBAMR_ADD_EXAMPLE(
  TARGET_NAME
    "IB-ex2-2d"
  OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/examples/IB/explicit/ex2"
  OUTPUT_NAME
    main2d
  EXAMPLE_GROUP
    examples-IB
  SOURCES
    example.cpp
  LINK_TARGETS
    IBAMR2d
  INPUT_FILES
    input2d
    )

IBAMR_ADD_EXAMPLE(
  TARGET_NAME
  "IB-ex2-2d-convergence"
  OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/examples/IB/explicit/ex2"
  OUTPUT_NAME
  main2d_convergence
  EXAMPLE_GROUP
  examples-IB
  SOURCES
  convergence_tester.cpp
  LINK_TARGETS
  IBAMR2d
  INPUT_FILES
  input2d.convergence)
