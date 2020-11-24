/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */
/** \file
 * \brief Millisecond CPU stopwatch for internal timing
 *
 *  Return the elapsed user+system CPU time in milliseconds
 *  since the most recent call.  Very much not thread-safe.
 */
#if defined (_WIN32)
#include <windows.h>
#else
#include <sys/times.h>
#include <unistd.h>
#endif
#include "scutil.h"

unsigned long
get_rutime(void)
{
static unsigned long last = 0;
unsigned long now, elapsed;

#if defined (_WIN32)
//TODO: using higher resolution counter?

now = GetTickCount();

elapsed = now - last;
last = now;

/*
static LARGE_INTEGER last = 0;
LARGE_INTEGER now, elapsed;
LARGE_INTEGER frequency;

QueryPerformanceFrequency(&frequency); 
QueryPerformanceCounter(&now);

elapsed.QuadPart = now.QuadPart - last.QuadPart;

//
// We now have the elapsed number of ticks, along with the
// number of ticks-per-second. We use these values
// to convert to the number of elapsed microseconds.
// To guard against loss-of-precision, we convert
// to microseconds *before* dividing by ticks-per-second.
//
elapsed.QuadPart *= 1000000;
elapsed.QuadPart /= freq.QuadPart;
*/
#else
  static long ticks_per_second = -1;

  struct tms tms;
 
  /* Initialize ticks_per_second. */
#ifdef _SC_CLK_TCK
  if (ticks_per_second <= 0)
    ticks_per_second = sysconf(_SC_CLK_TCK);
#endif /* _SC_CLK_TCK */
  if (ticks_per_second <= 0)
    ticks_per_second = 60; /* a traditional UNIX "jiffy" */

  times(&tms);
  now = tms.tms_utime + tms.tms_stime;
  now *= 1000; /* milliseconds */
  now /= ticks_per_second;

  elapsed = now - last;
  last = now;
#endif
  return elapsed;
}
