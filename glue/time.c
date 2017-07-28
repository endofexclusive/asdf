/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <time.h>
#include <dos/dos.h>
#include <clib/dos_protos.h>
#define dbg(ctx, ...)  msg(GLUE_LOG_TIME, "TIME:", ctx, __VA_ARGS__)
#include "dbg.h"

/*
 * The time() function shall return the value of time (in seconds since the
 * Epoch).
 *
 * The Amiga epoch starts at Jan 1, 1978 and AmigaDOS time format "DateStamp"
 * is very funny.
 *
 */
time_t time(time_t *tloc)
{
        dbg(NULL, "tloc=%p\n", (void *) tloc);
        /* Number of days from Amiga Epoch to Unix Epoch */
        const time_t U_TO_A_DAYS = 8 * 365 + 2;
        struct DateStamp ds;
        time_t ret;

        DateStamp(&ds);

        dbg(
                NULL, "  ds_Days=%lu, ds_Minute=%lu, ds_Tick=%lu\n",
                ds.ds_Days, ds.ds_Minute, ds.ds_Tick
        );

        ret =  U_TO_A_DAYS  * 24 * 60 * 60;
        ret += ds.ds_Days   * 24 * 60 * 60;
        ret += ds.ds_Minute           * 60;
        ret += ds.ds_Tick             / TICKS_PER_SECOND;

        if (tloc) {
                *tloc = ret;
        }
        dbg(NULL, "  ret=$%08lx\n", (unsigned long) ret);

        return ret;
}

