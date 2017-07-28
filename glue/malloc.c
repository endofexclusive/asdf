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

/*
 * According to RKRM, the Amiga system memory allocation functions return
 * memory blocks that are at least longword aligned.
 *
 * The following implementation supports malloc(0), which returns a pointer to
 * zero sized space, which can be passed to free() or realloc().
 */

void *_malloc_r(struct _reent *_r, size_t size)
{
        dbg(NULL, "_r=%p, size=%lu\n", (void *) _r, (unsigned long) size);
        struct dynmem_node *dn;
        ULONG bytesize;
        ULONG *p;

        (void) _r;
        bytesize = size + sizeof *dn;

        p = NULL;
        dn = AllocMem(bytesize, MEMF_ANY);
        if (dn) {
                dn->size = bytesize;
                AddTail((struct List *) &dynmem_list, (struct Node *) dn);
                p = dynmem_to_user(dn);
        }

        return p;
}

void *malloc(size_t size)
{
        return _malloc_r(_REENT, size);
}

