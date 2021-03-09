#
# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

add_definitions("-DILMTOOLBUILD")

# when crosscompiling import the executable targets from a file
IF(CMAKE_CROSSCOMPILING)
  SET(IMPORT_EXECUTABLES "IMPORTFILE-NOTFOUND" CACHE FILEPATH "Point it to the export file from a native build")
  FILE(TO_CMAKE_PATH "${IMPORT_EXECUTABLES}" IMPORT_PATH_CMAKE)
  INCLUDE(${IMPORT_PATH_CMAKE}/ImportExecutables.cmake)
ENDIF(CMAKE_CROSSCOMPILING)

if (NOT CMAKE_CROSSCOMPILING)
  add_executable(ilmtp
    ilmtp.cpp
    ${UTILS_COMMON_DIR}/utils.cpp
  )
  EXPORT(TARGETS ilmtp APPEND FILE ${CMAKE_BINARY_DIR}/ImportExecutables.cmake )

  target_include_directories(ilmtp
    PRIVATE
    ${UTILS_COMMON_DIR}
    ${FLANG_TOOLS_DIR}
    )
endif()


# Generate ILM tables

add_custom_command(
  OUTPUT ${UTILS_ILM_BIN_DIR}/ilmtpdf.h
         ${UTILS_ILM_BIN_DIR}/ilmtp.h
         ${UTILS_ILM_BIN_DIR}/ilmtp.n1
         ${FLANG2_DOC_BIN_DIR}/ilmtp.rst
  COMMAND ilmtp -I${UTILS_ILI_DIR} -l scftn
                                                 ${ARCH_DEP_ILM_DIR}/ilmtp.n
                                                 ${ARCH_DEP_ILI_DIR}/ilitp.n
                                              -o ${UTILS_ILM_BIN_DIR}/ilmtpdf.h
                                                 ${UTILS_ILM_BIN_DIR}/ilmtp.h
                                              -n ${UTILS_ILM_BIN_DIR}/ilmtp.n1
                                              -s ${FLANG2_DOC_BIN_DIR}/ilmtp.rst
  DEPENDS ilmtp ${ARCH_DEP_ILM_DIR}/ilmtp.n
                ${ARCH_DEP_ILM_DIR}/ilmtp_atomic.n
                ${ARCH_DEP_ILM_DIR}/ilmtp_longdouble.n
                ${ARCH_DEP_ILI_DIR}/ilitp.n
  )

add_custom_target(gen_backend_ilm
  SOURCES ${UTILS_ILM_BIN_DIR}/ilmtpdf.h
          ${UTILS_ILM_BIN_DIR}/ilmtp.h
          ${UTILS_ILM_BIN_DIR}/ilmtp.n1
          ${FLANG2_DOC_BIN_DIR}/ilmtp.rst
  )

# Local Variables:
# mode: cmake
# End:
