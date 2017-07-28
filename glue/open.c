/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <errno.h>
#include <fcntl.h>
#include <clib/dos_protos.h>
#include "fdnode.h"
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

#define NELEM(a) ((int) (sizeof (a) / sizeof (a[0])))

#undef errno
extern int errno;

/*
 *
 * NOTE: Newlib never calls open() on stdint, stdout and stderr.
 *
 * NOTE: Standard does not require fopen() to set errno on error.
 *
 * NOTE: Opening the a file with the same name multiple times with fopen() is
 * implementation dependent. (Portable code can not depend on it.)
 *
 * The implementation below will fail on the second fopen() in this example:
 *   fopen(path, "w")
 *   fopen(path, "r")
 * However, the behavior is compliant with the standard.
 */
int open(const char *path, int oflag, ...)
{
        dbg(NULL, "path=%s,  oflag=$%x\n", path, (unsigned int) oflag);
        short fd;
        BPTR fh;
        LONG fhmode;
        const char *fhmodestr = "";
        const char *oaccmode[4] = {"RDONLY", "WRONLY", "RDWR", "???"};

        /* Find a free file descriptor */
        fd = -1;
        for (short i = 3; i < NELEM(_fdnode); i++) {
                if (0 == _fdnode[i].fh) {
                        fd = i;
                        break;
                }
        }
        if (-1 == fd) {
                err(NULL, "no fd available\n");
                errno = ENFILE;
                return -1;
        }

        /* Do not care about "open()" mode */
        switch (oflag & (O_CREAT | O_TRUNC)) {
                case 0:
                        fhmode = MODE_OLDFILE;
                        fhmodestr = "OLDFILE";
                        break;
                case O_CREAT | O_TRUNC:
                        fhmode = MODE_NEWFILE;
                        fhmodestr = "NEWFILE";
                        break;
                case O_CREAT:
                        fhmode = MODE_READWRITE;
                        fhmodestr = "READWRITE";
                        break;
                default:
                        /* The value of the oflag argument is not valid. */
                        err(NULL, "bad oflag=$%x\n", (unsigned int) oflag);
                        errno = EINVAL;
                        return -1;
        }

        dbg(NULL,
                "O_%s %s %s -> MODE_%s ($%x)\n",
                oaccmode[oflag & O_ACCMODE],
                oflag & O_CREAT ? "O_CREAT" : "",
                oflag & O_TRUNC ? "O_TRUNC" : "",
                fhmodestr, (unsigned int) fhmode
        );

        fh = Open((CONST_STRPTR) path, fhmode);
        /* NOTE: Could set errno based on IoErr(). */
        if (!fh) {
                err(NULL, "Open() FAIL, IoErr()=%lu\n", IoErr());
                errno = EIO;
                return -1;
        }
        if (oflag & O_APPEND) {
                Seek(fh, 0, OFFSET_END);
        }

        _fdnode[fd].fh = fh;

        dbg(NULL, "fd=%hd\n", fd);
        return fd;
}

