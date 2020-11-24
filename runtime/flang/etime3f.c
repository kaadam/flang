/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

/* clang-format off */

/*	etime3f.c - Implements LIB3F etime subprogram.  */

#include "ent3f.h"

/* assumes the Unix times system call */

/* Not implemented for WINNT */
#ifndef _WIN32
#include <unistd.h>
#define _LIBC_LIMITS_H_
#include <sys/types.h>
#include <sys/times.h>
#include <limits.h>

#ifndef CLK_TCK
#define CLK_TCK sysconf(_SC_CLK_TCK)
#endif

float ENT3F(ETIME, etime)(float *tarray)
{
  struct tms b;
  float inv_ticks = 1 / (float)CLK_TCK;

  times(&b);
  tarray[0] = ((float)b.tms_utime) * inv_ticks;
  tarray[1] = ((float)b.tms_stime) * inv_ticks;
  return (tarray[0] + tarray[1]);
}
#else

float ENT3F(ETIME, etime)(float *tarray)
{
  // TODO: add implementation to get CPU system/user time.
 tarray[0] = 0;
 tarray[1] = 0; 
 return (tarray[0] + tarray[1]);
}
#endif
