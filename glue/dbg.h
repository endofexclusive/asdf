/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#ifndef GLUE_DBG_H_
#define GLUE_DBG_H_

/*
 * This file implements a simple log interface using the debug.lib function
 * KPutStr() which writes strings the Amiga serial port. Default is 9600 BAUD,
 * which can be overridden by calling glue_log_init().
 *
 * The value of GLUE_LOG specifies which log messages to generate. It can be
 * defined before inclusion of this header file, or by modifying the assignment
 * in this file.
 *
 * EXAMPLE:
 * #define GLUE_LOG (GLUE_LOG_ALL & ~GLUE_LOG_MEM & ~GLUE_LOG_DEBUG)
 * #include "dbg.h"
 */

/* Bit masks for GLUE_LOG */
/* Log levels */
#define GLUE_LOG_FAIL   0x0001
#define GLUE_LOG_ERROR  0x0002
#define GLUE_LOG_INFO   0x0004
#define GLUE_LOG_DEBUG  0x0008
/* Subsystems */
#define GLUE_LOG_SYS    0x0100
#define GLUE_LOG_FILE   0x0200
#define GLUE_LOG_TIME   0x0400
#define GLUE_LOG_MEM    0x0800

#define GLUE_LOG_NONE   0x0000
#define GLUE_LOG_ALL    0xffff

#ifndef GLUE_LOG
#if 1
 #define GLUE_LOG GLUE_LOG_NONE
#else
 #define GLUE_LOG (GLUE_LOG_ALL & ~GLUE_LOG_MEM)
#endif
#endif

#include <clib/debug_protos.h>
#include <stdio.h>

#define GLUE_LOG_BUFLEN 120
#define msg(p, msg, ctx, ...) \
        do { \
                char msg_buf[GLUE_LOG_BUFLEN]; \
                if (GLUE_LOG & p) { \
                        (void) ctx; \
                        snprintf(msg_buf, sizeof(msg_buf), "%-5s %10s: ", msg, __func__); \
                        KPutStr((CONST_STRPTR) msg_buf); \
                        snprintf(msg_buf, sizeof(msg_buf), __VA_ARGS__); \
                        KPutStr((CONST_STRPTR) msg_buf); \
                } \
        } while (0);

#ifndef dbg
 #define dbg(ctx, ...)  msg(GLUE_LOG_DEBUG, "DBG:", ctx, __VA_ARGS__)
#endif

#ifndef err
 #define err(ctx, ...)  msg(GLUE_LOG_ERROR, "ERR:", ctx, __VA_ARGS__)
#endif

/*
 * Set serial baud for log output. Probably only correct on PAL systems.
 */
static inline void glue_log_init(unsigned long baud)
{
        const unsigned long LOG_SERPER_CONST = 3546895;
        volatile unsigned short *const LOG_SERPER = (void *) (0xdff000 + 0x032);

        if (GLUE_LOG) {
                *LOG_SERPER = (LOG_SERPER_CONST / baud) - 1;
        }
}

#endif

