/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

/* clang-format off */

/*	sleep3f.c - Implements LIB3F sleep subprogram.  */

#include "ent3f.h"

#if defined(WIN64) || defined(_WIN32)

#include <windows.h>

void ENT3F(SLEEP, sleep)(t) unsigned int *t;
{
  Sleep(1000 * (*t)); /* MS Sleep() is in terms of milliseconds */
}
#else

#include <unistd.h>

void ENT3F(SLEEP, sleep)(t) unsigned int *t;
{
  sleep(*t);
}

#endif
