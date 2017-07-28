#ifndef GLUE_DYNMEM_H
#define GLUE_DYNMEM_H

#include <exec/lists.h>

/*
 * AllocMem() is used to allocate memory requested by malloc() and calloc().
 * Allocated size is the requested size plus a struct dynmem_node which is
 * located before the users memory area. The nodes are linked together on
 * the global dynmem_list.
 */
struct dynmem_node {
        struct MinNode node;
        ULONG size;
};

extern struct MinList dynmem_list;
void __dynmem_init(void);
void __dynmem_shutdown(void);

static inline void *dynmem_to_user(struct dynmem_node *dn)
{
        return &dn[1];
}

static inline struct dynmem_node *user_to_dynmem(void *user)
{
        struct dynmem_node *dn = user;
        return &dn[-1];
}

#endif

