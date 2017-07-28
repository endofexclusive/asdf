/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <unistd.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_SYS, "SYS:", ctx, __VA_ARGS__)
#include "dbg.h"

int getpid(void)
{
        dbg(NULL, "\n");

        return 1;
}

