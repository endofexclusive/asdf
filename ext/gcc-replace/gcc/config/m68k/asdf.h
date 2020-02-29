/* Configuration file for an m68k ASDF target. */

#undef CPP_SPEC
#define CPP_SPEC "-isystem %R/include_h"

/*
 * -fleading-underscore is essential to link with precompiled Amiga libraries
 */
#undef CC1_SPEC
#define CC1_SPEC "-fleading-underscore -fomit-frame-pointer"

#undef LINK_SPEC
#define LINK_SPEC \
" \
-Cgnu -Bstatic -bamigahunk -S -nostdlib -sc -gc-all -L%R/linker_libs \
%{-target-help:-h} \
%{-help:-h} \
"

/* NOTE: -lg is same as -lc with Newlib (hard link in file system) */
/* TODO: get rid of -lamiga dependency */
#undef  LIB_SPEC
#define LIB_SPEC "-lglue -lc -lamiga"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
" \
%{!qnstart: ustart.o%s} \
%{qnstart: nstart.o%s} \
"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC ""

#undef LINKER_NAME
#define LINKER_NAME "asdf-vlink"

