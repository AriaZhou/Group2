# Copyright (c) 2021 Pei-Ru Wang, Cheryl Huang, Yuan Zhou. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.14)

add_executable(httpserver 
  PUBLIC 
    ${HEADER_FILE} 
  PRIVATE 
    ${SOURCE_FILE}
)

target_include_directories(httpserver ${SRC_DIR}/include)
