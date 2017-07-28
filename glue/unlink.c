/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

/*
 * NOTE: Probably better to implement remove() directly instead of indirecting
 * with unlink()
 */

#include <unistd.h>
#include <errno.h>
#include <dos/dos.h>
#include <clib/dos_protos.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

#undef errno
extern int errno;

int unlink(const char *path)
{
        dbg(NULL, "path=%s\n", path);
        BOOL success;

        success = DeleteFile((CONST_STRPTR) path);
        if (FALSE == success) {
                dbg(NULL, "DeleteFile(%s) returned failure\n", path);
                errno = ENOENT;
                return -1;
        }
        dbg(NULL, "DeleteFile(%s) returned success\n", path);

        return 0;
}

