#ifndef XPROTO_H_
#define XPROTO_H_

/*
 * Inline function calls to library routines.
 *
 * NOTE: These functions assume a6 is preserved by all library routines.
 */

#include <exec/types.h>

#define EXEC_BASE_NAME SysBase
extern struct ExecBase *SysBase;

static inline struct Library *OpenLibrary(
        CONST_STRPTR ___libName,
        ULONG ___version
)
{
  register struct Library * _res __asm("d0");
  register struct ExecBase * _base __asm("a6") = EXEC_BASE_NAME;
  register CONST_STRPTR libName __asm("a1") = ___libName;
  register ULONG version __asm("d0") = ___version;
  __asm volatile ("jsr %%a6@(-552:W)"
  : "=r" (_res)
  : "r" (_base), "r" (libName), "r" (version)
  : "d1", "a0", "cc", "memory");
  return _res;
}

static inline void CloseLibrary(
        struct Library * ___library
)
{
  register struct ExecBase * _base __asm("a6") = EXEC_BASE_NAME;
  register struct Library * library __asm("a1") = ___library;
  __asm volatile ("jsr %%a6@(-414:W)"
  : /* No output */
  : "r" (_base), "r" (library)
  : "d0", "d1", "a0", "cc");
}

static inline void Disable(void)
{
  register struct ExecBase * _base __asm("a6") = EXEC_BASE_NAME;
  __asm volatile ("jsr %%a6@(-120:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void Enable(void)
{
  register struct ExecBase * _base __asm("a6") = EXEC_BASE_NAME;
  __asm volatile ("jsr %%a6@(-126:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void Forbid(void)
{
  register struct ExecBase * _base __asm("a6") = EXEC_BASE_NAME;
  __asm volatile ("jsr %%a6@(-132:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void Permit(void)
{
  register struct ExecBase * _base __asm("a6") = EXEC_BASE_NAME;
  __asm volatile ("jsr %%a6@(-138:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}


#define GFX_BASE_NAME GfxBase
extern struct GfxBase *GfxBase;

static inline void OwnBlitter(void)
{
  register struct GfxBase * _base __asm("a6") = GFX_BASE_NAME;
  __asm volatile ("jsr %%a6@(-456:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void DisownBlitter(void)
{
  register struct GfxBase * _base __asm("a6") = GFX_BASE_NAME;
  __asm volatile ("jsr %%a6@(-462:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void WaitBlit(void)
{
  register struct GfxBase * _base __asm("a6") = GFX_BASE_NAME;
  __asm volatile ("jsr %%a6@(-228:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void WaitTOF(void)
{
  register struct GfxBase * _base __asm("a6") = GFX_BASE_NAME;
  __asm volatile ("jsr %%a6@(-270:W)"
  : /* No output */
  : "r" (_base)
  : "d0", "d1", "a0", "a1", "cc");
}

static inline void LoadView(
        struct View * ___view
)
{
  register struct GfxBase * _base __asm("a6") = GFX_BASE_NAME;
  register struct View * view __asm("a1") = ___view;
  __asm volatile ("jsr %%a6@(-222:W)"
  : /* No output */
  : "r" (_base), "r" (view)
  : "d0", "d1", "a0", "cc");
}

#endif

