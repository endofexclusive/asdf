#include <stdint.h>
#include <exec/types.h>
#include <hardware/custom.h>
#include <graphics/gfxbase.h>
#include <asdf/custombits.h>

#if 1
 /* Use inline functions for library routines (fast) */
 #include "xproto.h"
#else
 /* Use stubs from amiga.lib for library routines (slow) */
 #include <clib/exec_protos.h>
 #include <clib/graphics_protos.h>
#endif

#include "cust.h"

#define UNUSED(v) (void) (sizeof (v))

struct GfxBase *GfxBase;

struct wbstate {
        UWORD dmacon;
        UWORD intena;
        UWORD intreq;
        struct View *ActiView;
        struct copinit *copinit;
};
static struct wbstate wbstate;

static int sys_down(void)
{
        cust_init();
        GfxBase = (struct GfxBase *) OpenLibrary((CONST_STRPTR) "graphics.library", 33);
        if (NULL == GfxBase) {
                return 1;
        }

        OwnBlitter();
        WaitBlit();
        Forbid();

        wbstate.ActiView = GfxBase->ActiView;
        wbstate.copinit = GfxBase->copinit;
        LoadView(NULL);
        WaitTOF();
        WaitTOF();

        /* Mitigate against potential race between read and write. */
        Disable();
        wbstate.intena = cust->intenar;
        cust->intena = (UWORD) ~INTF_SETCLR;
        cust->intreq = (UWORD) ~INTF_SETCLR;
        wbstate.dmacon = cust->dmaconr;
        cust->dmacon = (UWORD) ~DMAF_SETCLR;

        return 0;
}

static void sys_up(void)
{
        cust->intena = (UWORD) ~INTF_SETCLR;
        cust->dmacon = (UWORD) ~DMAF_SETCLR;
        cust->intreq = (UWORD) ~INTF_SETCLR;
        cust->intreq = INTF_SETCLR | wbstate.intreq;
        cust->dmacon = DMAF_SETCLR | wbstate.dmacon;
        cust->intena = INTF_SETCLR | wbstate.intena;
        Enable();

        LoadView(wbstate.ActiView);
        cust->cop1lc = (ULONG) wbstate.copinit;
        cust->copjmp1 = 0;

        Permit();
        DisownBlitter();

        CloseLibrary((struct Library *) GfxBase);
}

void demo(void);

int main(int argc, char **argv)
{
        UNUSED(argc);
        UNUSED(argv);

        if (0 != sys_down()) {
                return 1;
        }
        demo();
        sys_up();

        return 0;
}

