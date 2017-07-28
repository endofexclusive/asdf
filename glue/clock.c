/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <time.h>
#include <dos/dos.h>
#include <clib/dos_protos.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_TIME, "TIME:", ctx, __VA_ARGS__)
#include "dbg.h"

#if (CLOCKS_PER_SEC != TICKS_PER_SECOND * 20)
 #error CLOCKS_PER_SEC
#endif
#define CLOCKS_PER_TICK (CLOCKS_PER_SEC / TICKS_PER_SECOND)

clock_t clock(void)
{
        dbg(NULL, "NOTE: The Amiga operating system can not tell CPU time.\n");
        struct DateStamp ds;
        clock_t ret;

        DateStamp(&ds);

        dbg(
                NULL, "  ds_Days=%lu, ds_Minute=%lu, ds_Tick=%lu\n",
                ds.ds_Days, ds.ds_Minute, ds.ds_Tick
        );

        ret  = ds.ds_Minute * 60 * CLOCKS_PER_SEC;
        ret += ds.ds_Tick        * CLOCKS_PER_TICK;

        dbg(NULL, "  %ld ms\n", ret);

        return ret;
}

