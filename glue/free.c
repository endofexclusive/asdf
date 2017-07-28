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

void _free_r(struct _reent *_r, void *ptr)
{
        dbg(NULL, "_r=%p, ptr=%p\n", (void *) _r, (void *) ptr);
        struct dynmem_node *dn;

        (void) _r;
        if (NULL == ptr) {
                return;
        }

        dn = user_to_dynmem(ptr);
        Remove((struct Node *) dn);
        FreeMem(dn, dn->size);
}

void free(void *ptr)
{
        _free_r(_REENT, ptr);
}

