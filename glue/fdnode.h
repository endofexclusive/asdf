/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#ifndef GLUE_FDNODE_H_
#define GLUE_FDNODE_H_

#include <stdio.h>
#include <dos/dos.h>

/* NOTE: missing in newlib / POSIX limits.h */
#ifndef SSIZE_MAX
 #ifndef _POSIX_SSIZE_MAX
  #define _POSIX_SSIZE_MAX 32767
 #endif
 #define SSIZE_MAX _POSIX_SSIZE_MAX
#endif

#define NFDNODE 32

#if !defined(FOPEN_MAX) || NFDNODE < FOPEN_MAX
 #error FOPEN_MAX is too large
#endif

struct fdnode {
        BPTR fh;
};

/*
 * cli startup: stdin, stdout should be taken from Input() and Output() at C
 * run-time init. Could be set by system (Shell) to file (redirection),
 * including NIL:
 *
 * wb startup: system probably sets Input()/Output() to NIL:
 *
 * cli/wb: stderr should open a separate CONSOLE: or "*" window, since DOS (?)
 * does not seem to have a stderr concept. Shell V45 seem to have stderr
 * redirection, what that means.
 */
extern struct fdnode _fdnode[NFDNODE];

void __fdnode_init(void);
void __fdnode_shutdown(void);

#endif

