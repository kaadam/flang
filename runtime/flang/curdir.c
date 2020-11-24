/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

#include <sys/types.h>
#ifndef _WIN32
#include <sys/param.h>
#include <sys/utsname.h>
#else
#include <direct.h>
#include <windows.h>
#endif
#include <stdlib.h>
#include "stdioInterf.h"
#include "fioMacros.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

#if defined(_WIN32) || defined(_WIN64)
#define getcwd _getcwd
#endif

extern char *getcwd();
extern char *__fort_getopt();

WIN_MSVCRT_IMP char *WIN_CDECL getenv(const char *);

/* fix pathname for "funny" NFS mount points */

void __fort_fixmnt(new, old) char *new;
char *old;
{
  char *q;
  char s[MAXPATHLEN]; /* substitute patterns */
  char *smat;         /* match string */
  char *srep;         /* replace string */
  char *snxt;         /* next pattern */
  int n;

  q = __fort_getopt("-mount"); /* pattern */
  if (q == NULL) {
    q = "/tmp_mnt";
  }
  strcpy(s, q);

  snxt = s;
  while (snxt != NULL) {
    smat = snxt;
    snxt = strchr(snxt, ',');
    if (snxt != NULL) {
      *snxt = '\0';
      snxt++;
    }
    srep = strchr(smat, ':'); /* replace string */
    if (srep == NULL) {
      srep = "";
    } else {
      *srep = '\0';
      srep++;
    }
    n = strlen(smat); /* match string length */
    if (strncmp(old, smat, n) == 0) {
      strcpy(new, srep);
      strcat(new, old + n);
      return;
    }
  }
  strcpy(new, old);
}

/* get current working directory */

void __fort_getdir(curdir) char *curdir;
{
  char path[MAXPATHLEN];
  char *p;

  p = getcwd(path, MAXPATHLEN);
  if (p == NULL) {
    p = getenv("PWD");
    if (p == NULL) {
      __fort_abort("cannot find current directory\n");
    }
    strcpy(path, p);
  }
  __fort_fixmnt(curdir, path);
}

/* get current hostname */
//TODO: Refactor this
#ifndef _WIN32
void __fort_gethostname(host) char *host;
{
  struct utsname un;
  char *p;
  int s;

  p = __fort_getopt("-curhost");
  if (p == NULL) {
    s = uname(&un); /* get hostname */
    if (s == -1) {
      __fort_abortp("uname");
    }
    p = un.nodename;
  }
  strcpy(host, p);
}
#else
void __fort_gethostname(host) char *host;
{
  char *p;
  int s;

  p = __fort_getopt("-curhost");
  if (p == NULL) {
    wchar_t buffer[MAX_PATH] = {0};
    DWORD size = MAX_PATH;
    
    if (!GetComputerNameEx(ComputerNameDnsFullyQualified, buffer, &size)) {
      s = -1;
    }
    if (s == -1) {
      __fort_abortp("uname");
    }
    p = (char *)malloc( MAX_PATH );
    wcstombs(p, &buffer, MAX_PATH);
  }
  strcpy(host, p);
}
#endif
