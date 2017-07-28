/*
 * Copyright (c) 2017, Martin Aberg. All rights reserved.
 * Licensed under the FreeBSD license.
 */

#include <stdlib.h>
#include <exec/types.h>
#include <clib/exec_protos.h>
#include "dynmem.h"
#define dbg(ctx, ...)  msg(GLUE_LOG_MEM, "MEM:", ctx, __VA_ARGS__)
#include "dbg.h"

void *_realloc_r(struct _reent *_r, void *ptr, size_t size)
{
        dbg(NULL, "_r=%p, ptr=%p, size=%lu\n", (void *) _r, (void *) ptr, (unsigned long) size);
        ULONG *newp;
        ULONG copybytesize;

        (void) _r;
        if (NULL == ptr) {
                return malloc(size);
        }

        newp = malloc(size);

        if (NULL == newp) {
                return NULL;
        }

        copybytesize = user_to_dynmem(ptr)->size - sizeof (struct dynmem_node);
        if (size < copybytesize) {
                copybytesize = size;
        }
        CopyMem(ptr, newp, copybytesize);
        free(ptr);

        return newp;
}

void *realloc(void *ptr, size_t size)
{
        return _realloc_r(_REENT, ptr, size);
}

