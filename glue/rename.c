/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <stdio.h>
#include <clib/dos_protos.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

extern int errno;

int _rename(const char *old, const char *new)
{
        dbg(NULL, "old=%s, new=%s\n", old, new);
        BOOL success;

        success = Rename((CONST_STRPTR) old, (CONST_STRPTR) new);
        if (FALSE == success) {
                dbg(NULL, "Rename() returned failure\n");
                return -1;
        }

        return 0;
}

