/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */


/**
 *  \file
 *  Declare routines that access the machine registers
 */

#include "flangrti_config.h"

#if defined(HAVE_GREGSET_T)
void dumpregs(gregset_t *regs);
gregset_t *getRegs(ucontext_t *u);
#else
void dumpregs(void *regs);
void *getRegs(void *u);
#endif
