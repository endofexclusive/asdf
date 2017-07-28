/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <unistd.h>
#include <clib/dos_protos.h>
#include "fdnode.h"

#define NELEM(a) ((int) (sizeof (a) / sizeof (a[0])))

/*
 * cli startup: stdin, stdout should be taken from Input() and Output() at C
 * run-time init. Could be set by system (Shell) to file (redirection),
 * including NIL:
 *
 * wb startup: system probably sets Input()/Output() to NIL:
 *
 * cli/wb: stderr should open a separate CONSOLE: or "*" window, since DOS (?)
 * does not seem to have a stderr concept. Shell V45 seems to have stderr
 * redirection, whatever that means.
 *
 * NOTE: Handlers for std{in,out,err} are installed by startup code.
 */
struct fdnode _fdnode[NELEM(_fdnode)];

void __fdnode_init(void)
{
        BPTR fh;

        fh = Input();
        _fdnode[STDIN_FILENO].fh = fh;
        fh = Output();
        _fdnode[STDOUT_FILENO].fh = fh;
        _fdnode[STDERR_FILENO].fh = fh;
}

void __fdnode_shutdown(void)
{
        for (short i = 3; i < NELEM(_fdnode); i++) {
                BPTR fh;

                fh = _fdnode[i].fh;
                if (fh) {
                        Close(fh);
                }
        }
}

