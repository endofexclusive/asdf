/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <unistd.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

/*
 * The isatty() function shall return 1 if fildes is associated with a
 * terminal; otherwise, it shall return 0 and may set errno to indicate the
 * error.
 */
int isatty(int fildes)
{
        if (
                STDIN_FILENO  == fildes ||
                STDOUT_FILENO == fildes ||
                STDERR_FILENO == fildes
        ) {
                return 1;
        } else {
                return 0;
        }
}

