/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <unistd.h>
#include <clib/dos_protos.h>
#include "fdnode.h"
#define dbg(ctx, ...)  msg(GLUE_LOG_FILE, "FILE:", ctx, __VA_ARGS__)
#include "dbg.h"

#undef errno
extern int errno;

/*
 * NOTE: This implementation does not allow setting offset beyond end of
 * existing data.
 */
off_t lseek(int fildes, off_t offset, int whence)
{
        dbg(NULL, "fildes=%d, offset=%ld, whence=$%x\n", fildes, offset, whence);
        BPTR fh;
        LONG mode;
        LONG seekret;
        const char *whence_mode;

        fh = _fdnode[fildes].fh;

        if (SEEK_SET == whence) {
                mode = OFFSET_BEGINNING;
                whence_mode = "SET -> OFFSET_BEGINNING";
        } else if (SEEK_CUR == whence) {
                mode = OFFSET_CURRENT;
                whence_mode = "CUR -> OFFSET_CURRENT";
        } else {
                mode = OFFSET_END;
                whence_mode = "END -> OFFSET_END";
        }
        seekret = Seek(fh, offset, mode);
        dbg(NULL, "SEEK_%s (%ld)\n", whence_mode, seekret);

        if (
                (seekret == -1) ||

                /*
                 * Workaround for V36 and V37 ROM filesystem which returns the
                 * current position on error and sets IoErr().
                 */
                ((0 <= seekret) && (IoErr() == ERROR_SEEK_ERROR))
        ) {
                dbg(NULL, "IoErr() = %ld\n", IoErr());
                return -1;
        }
        seekret = Seek(fh, 0, OFFSET_CURRENT);

        return seekret;
}

