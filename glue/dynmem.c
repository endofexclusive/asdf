#include <clib/alib_protos.h>
#include <clib/exec_protos.h>
#include "dynmem.h"

struct MinList dynmem_list;

void __dynmem_init(void)
{
        NewList((struct List *) &dynmem_list);
}

void __dynmem_shutdown(void)
{
        struct Node *node;

        while ((node = RemHead((struct List *) &dynmem_list))) {
                struct dynmem_node *dn;

                dn = (struct dynmem_node *) node;
                FreeMem(dn, dn->size);
        }
}

/* Compile time check so we can guarantee long-aligned memory allocation. */
enum {
        __assert_dynmem_node_is_long_aligned =
        (1 / (0 == ((sizeof (struct dynmem_node)) % 4)) ? 1 : 0)
};

