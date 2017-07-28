/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <sys/stat.h>
#include <unistd.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

/*
 * Newlib examines only a very limited set of parameters.
 *   newlib/libc/stdio$ git grep "\.st_"
 *
 * - st_mode (S_IFREG, S_IFCHR, S_IFDIR)
 * - st_size (only for used for Red Hat EL/IX higher levels)
 */

int fstat(int fildes, struct stat *buf)
{
        dbg(NULL, "fildes=%d, buf=%p\n", fildes, (void *) buf);
        buf->st_size = 0;
        if (
                STDIN_FILENO  == fildes ||
                STDOUT_FILENO == fildes ||
                STDERR_FILENO == fildes
        ) {
                buf->st_mode = S_IFCHR;
        } else {
                buf->st_mode = S_IFREG;
        }

        return 0;
}

