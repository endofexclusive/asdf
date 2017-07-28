/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <errno.h>
#include <signal.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_SYS, "SYS:", ctx, __VA_ARGS__)
#include "dbg.h"

#undef errno
extern int errno;

int kill(int pid, int sig)
{
        dbg(NULL, "pid=%d, sig=%d\n", pid, sig);
        errno = EINVAL;

        return -1;
}

