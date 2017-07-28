/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <stdlib.h>
#include <string.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <exec/libraries.h>
#include <clib/exec_protos.h>
#include "dynmem.h"
#include "fdnode.h"

int main(int argc, char **argv);

struct Library *SysBase;
struct Library *DOSBase;

struct bcpl_string {
        UBYTE len;
        UBYTE data[];
};

/* Calculate a lower limit for argc */
static int calc_argc(
        const char *cmdline
)
{
        int argc = 1;

        if ('\n' != *cmdline) {
                argc++;
        }
        while (1) {
                int c;

                c = *cmdline;
                cmdline++;
                if ('\n' == c) {
                        break;
                } else if (' ' == c) {
                        argc++;
                        while (' ' == *cmdline) {
                                cmdline++;
                        }
                }
        }

        return argc;
}

static struct bcpl_string *get_cmdname(void)
{
        struct Process *proc;
        struct CommandLineInterface *cli;

        proc = (struct Process *) FindTask(NULL);
        cli = BADDR(proc->pr_CLI);
        return BADDR(cli->cli_CommandName);
}

/*
 * Generate argc and argv.
 *
 * NOTE: It is guaranteed that argc is non-negative and that argv[argc] is
 * NULL.
 *
 * Dynamic memory will be deallocated in _exit().
 */
static void gen_argv(
        const char *cmdline,
        unsigned long cmdlen,
        int *argc_user,
        char ***argv_user
)
{
        int argc;
        char **argv;
        char **argvp;
        char *argbuf;
        int argbuflen;
        struct bcpl_string *cmdname;
        char *p;
        int startword;

        cmdname = get_cmdname();
        /* add for NUL character. */
        argbuflen = cmdname->len + 1;
        /* subtract for newline and add for NUL character. */
        argbuflen += (cmdlen - 1 + 1);
        argbuf = malloc(argbuflen);
        if (NULL == argbuf) {
                return;
        }

        /* A lower limit of argc. Calculated exactly later. */
        argc = calc_argc(cmdline);
        /* + 1 is for the NULL entry */
        argv = malloc((argc + 1) * sizeof (char *));
        if (NULL == argv) {
                return;
        }
        argvp = argv;
        p = &argbuf[0];

        /* argv[0] */
        *argvp++ = p;
        memcpy(p, cmdname->data, cmdname->len);
        p += cmdname->len;
        *p++ = '\0';

        startword = 1;
        argc = 1;
        while (1) {
                int c;

                c = *cmdline++;
                if ('\n' == c) {
                        *p = '\0';
                        break;
                }
                if (' ' == c) {
                        *p = '\0';
                        while (' ' == *cmdline) {
                                cmdline++;
                        }
                        startword = 1;
                } else {
                        *p = c;
                        if (startword) {
                                *argvp++ = p;
                                argc++;
                                startword = 0;
                        }
                }
                p++;
        }
        argv[argc] = NULL;

        *argc_user = argc;
        *argv_user = argv;
}

/*
 * IF this function returns to caller THEN
 *   main() was never called
 * ELSE
 *   _exit() will be called at some point (via exit() or abort())
 * END IF
 */
void __ustart_main(
        /* Command line, excl. command, plus a newline. not terminated */
        const char *cmdline,
        /* Number of bytes in cmdline. */
        unsigned long cmdlen
)
{
        SysBase = *((struct Library **) 4);
        DOSBase = OpenLibrary((CONST_STRPTR) "dos.library", 33);
        if (NULL == DOSBase) {
                return;
        }
        __dynmem_init();
        __fdnode_init();

        int ret;
        int argc = 0;
        char **argv = { NULL };

        gen_argv(cmdline, cmdlen, &argc, &argv);
        ret = main(argc, argv);
        exit(ret);
        /* Never returns */
}

void __ustart__exit_main(void)
{
        __fdnode_shutdown();
        __dynmem_shutdown();
        CloseLibrary(DOSBase);
}

