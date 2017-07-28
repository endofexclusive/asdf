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

void *_calloc_r(struct _reent *_r, size_t nelem, size_t elsize)
{
        dbg(NULL, "_r=%p, nelem=%lu, elsize=%lu\n", (void *) _r, (unsigned long) nelem, (unsigned long) elsize);
        struct dynmem_node *dn;
        ULONG bytesize;
        ULONG *p;

        (void) _r;
        /* NOTE: Does not handle overflow */
        bytesize = nelem * elsize + sizeof *dn;

        p = NULL;
        dn = AllocMem(bytesize, MEMF_ANY | MEMF_CLEAR);
        if (dn) {
                dn->size = bytesize;
                AddTail((struct List *) &dynmem_list, (struct Node *) dn);
                p = dynmem_to_user(dn);
        }

        return p;
}

void *calloc(size_t nelem, size_t elsize)
{
        return _calloc_r(_REENT, nelem, elsize);
}

