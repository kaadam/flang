#
# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

if (NOT CMAKE_CROSSCOMPILING)
  add_executable(errmsggen
    errmsg.cpp
  )
  EXPORT(TARGETS errmsggen APPEND FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake )
endif()
