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
  add_executable(fmachar
    ${UTILS_SHARED_DIR}/machar.cpp
    ${UTILS_COMMON_DIR}/utils.cpp
    )
  EXPORT(TARGETS fmachar APPEND FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake )

  target_include_directories(fmachar
    PRIVATE
    ${FLANG_INCLUDE_DIR}
    ${UTILS_COMMON_DIR}
    )
endif()


# Generate Machar headers

add_custom_command(
  OUTPUT ${UTILS_MACHAR_BIN_DIR}/machar.h
         ${UTILS_MACHAR_BIN_DIR}/machardf.h
  COMMAND fmachar ${UTILS_MACHAR_DIR}/machar.n
                                          ${UTILS_SYMTAB_BIN_DIR}/symtab.h
                                       -o ${UTILS_MACHAR_BIN_DIR}/machar.h
                                          ${UTILS_MACHAR_BIN_DIR}/machardf.h
  DEPENDS gen_backend_symtab fmachar ${UTILS_MACHAR_DIR}/machar.n ${UTILS_SYMTAB_BIN_DIR}/symtab.h
  )

add_custom_target(gen_backend_machar
  SOURCES ${UTILS_MACHAR_BIN_DIR}/machar.h
          ${UTILS_MACHAR_BIN_DIR}/machardf.h
  )

# Local Variables:
# mode: cmake
# End:
