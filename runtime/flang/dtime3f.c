/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

/* clang-format off */

/*	dtime3f.c - Implements LIB3F dtime subprogram.  */

/* assumes the Unix times system call */
/* how do we do this for WINNT */
#include "ent3f.h"

#ifndef _WIN32

#define _LIBC_LIMITS_H_
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <limits.h>

#ifndef CLK_TCK
#define CLK_TCK sysconf(_SC_CLK_TCK)
#endif

static clock_t accum_user = 0, accum_sys = 0;

float ENT3F(DTIME, dtime)(float *tarray)
{
  struct tms b;
  float inv_ticks = 1 / (float)CLK_TCK;

  times(&b);
  tarray[0] = ((float)(b.tms_utime - accum_user)) * inv_ticks;
  tarray[1] = ((float)(b.tms_stime - accum_sys)) * inv_ticks;
  accum_user = b.tms_utime;
  accum_sys = b.tms_stime;
  return (tarray[0] + tarray[1]);
}

#else
float ENT3F(DTIME, dtime)(float *tarray)
{
  tarray[0] = 0;
  tarray[1] = 0;
  return (tarray[0] + tarray[1]);
}

#endif