#
# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

# when crosscompiling import the executable targets from a file
IF(CMAKE_CROSSCOMPILING)
  SET(IMPORT_EXECUTABLES "IMPORTFILE-NOTFOUND" CACHE FILEPATH "Point it to the export file from a native build")
  FILE(TO_CMAKE_PATH "${IMPORT_EXECUTABLES}" IMPORT_PATH_CMAKE)
  INCLUDE(${IMPORT_PATH_CMAKE}/ImportExecutables.cmake)
ENDIF(CMAKE_CROSSCOMPILING)

if (NOT CMAKE_CROSSCOMPILING)
  add_executable(astutil
    astutil.c
    ${UTILS_COMMON_DIR}/utils.cpp
    )
  EXPORT(TARGETS astutil APPEND FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake )

  target_include_directories(astutil
    PRIVATE
    ${FLANG_INCLUDE_DIR}
    ${UTILS_COMMON_DIR}
    ${TOOLS_SHARED_DIR}
    ${FLANG1_SRC_DIR}
    ${FLANG1_INCLUDE_DIR}
    )
endif()


# Generate AST headers

add_custom_command( 
  OUTPUT ${UTILS_AST_BIN_DIR}/ast.out.n ${UTILS_AST_BIN_DIR}/ast.h ${UTILS_AST_BIN_DIR}/astdf.h
  COMMAND astutil ${UTILS_AST_DIR}/ast.n ${UTILS_AST_DIR}/ast.in.h ${UTILS_SYMTAB_BIN_DIR}/ast.d ${UTILS_SYMTAB_BIN_DIR}/astdf.d -o -n ${UTILS_AST_BIN_DIR}/ast.out.n ${UTILS_AST_BIN_DIR}/ast.h ${UTILS_AST_BIN_DIR}/astdf.h
  DEPENDS gen_frontend_symini astutil ${UTILS_AST_DIR}/ast.n ${UTILS_AST_DIR}/ast.in.h ${UTILS_SYMTAB_BIN_DIR}/ast.d ${UTILS_SYMTAB_BIN_DIR}/astdf.d
  )

add_custom_target(gen_frontend_ast
  SOURCES ${UTILS_AST_BIN_DIR}/ast.out.n ${UTILS_AST_BIN_DIR}/ast.h ${UTILS_AST_BIN_DIR}/astdf.h
  )
