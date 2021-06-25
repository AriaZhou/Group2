# Copyright (c) 2021 Pei-Ru Wang, Cheryl Huang, Yuan Zhou. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.14)

find_package(GTest)

if(GTEST_FOUND)
  add_executable(unit_tests 
    PUBLIC 
      ${HEADER_FILE} 
    PRIVATE 
      ${SOURCE_FILE} 
      ${TEST_SOURCE_FILE} 
  )

  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

  set_target_properties(httpserver PROPERTIES ENABLE_EXPORTS on)

  target_link_libraries(unit_tests 
    PUBLIC
      ${GTEST_BOTH_LIBRARIES}
      httpserver
  )

  target_include_directories(unit_tests 
    PUBLIC
      ${GTEST_INCLUDE_DIRS}
  )
endif()
