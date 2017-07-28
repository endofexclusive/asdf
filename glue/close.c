/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <errno.h>
#include <unistd.h>
#include <clib/dos_protos.h>
#include "fdnode.h"
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

#undef errno
extern int errno;

/* Assumes fclose() calls us with fd opened with open(). */
int close(int fildes)
{
        dbg(NULL, "fildes=%d\n", fildes);
        BPTR fh;

        /*
         * NOTE: AUTODOCS says
         *   "Never close the filehandle returned by Input()/Output()"
         *
         * NOTE: fclose() on stin/out/err is implementation dependent.
         * freopen() is typically used instead.
         */
        if (
                STDIN_FILENO  == fildes ||
                STDOUT_FILENO == fildes ||
                STDERR_FILENO == fildes
        ) {
                err(NULL, "fd=%d not allowed\n", fildes);
                errno = EACCES;
                return -1;
        }

        fh = _fdnode[fildes].fh;
        _fdnode[fildes].fh = 0;

        /* NOTE: Return value did not exist before V36 */
        Close(fh);

        return 0;
}

