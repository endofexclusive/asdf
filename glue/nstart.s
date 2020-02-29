; nano start
; Fast and simple for applications not using the C standard library. SysBase is
; initialized. All other AmigaOS libraries have to be opened by the user.

        xdef    ___nstart
        xdef    _SysBase

        section code
; a0: Command line, excl. command, plus a newline. not terminated
; d0: Number of bytes in cmdline
___nstart:
        move.l  4.W, _SysBase
; NOTE: It is guaranteed that argc is non-negative and that argv[argc] is NULL.
; argv
        move.l  #___nstart_null, -(sp)
; argc
        clr.l   -(sp)
        jsr     _main
        addq.l  #8, sp

; DOS return code is d0 interpreted as a LONG. Assume main() does not depend on
; int being 32-bit.
        ext.l   d0

        rts

        section bss
___nstart_null:
        ds.l    1

_SysBase:
        ds.l    1

