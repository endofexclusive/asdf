/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <dos/dos.h>
#include <clib/dos_protos.h>
#include "fdnode.h"
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

#undef errno
extern int errno;

ssize_t write(int fildes, const void *buf, size_t nbyte)
{
        dbg(NULL, "fildes=%d, buf=%p, nbyte=%lu\n", fildes, buf, nbyte);
        BPTR fh;
        ssize_t nwritten;

        if (LONG_MAX < nbyte) {
                nbyte = LONG_MAX;
        }
        if (SSIZE_MAX < nbyte) {
                nbyte = SSIZE_MAX;
        }

        /* Relies on C library to provide valid parameters. */
        fh = _fdnode[fildes].fh;
        nwritten = Write(fh, (void *) buf, nbyte);
        if (-1 == nwritten) {
                errno = EIO;
        }

        return nwritten;
}

