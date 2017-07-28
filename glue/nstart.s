; pico start
; Fast and simple for applications not using the C standard library. Simple C
; standard library functions without system side-effects should work however.
; All AmigaOS libraries have to be opened by the user, including initializing
; SysBase.

        xdef    ___nstart
        xdef    _SysBase

        section code
___nstart:
        move.l  4.W, _SysBase
; NOTE: It is guaranteed that argc is non-negative and that argv[argc] is NULL.
; argv
        move.l  #___nstart_null, -(sp)
; argc
        clr.l   -(sp)
        jsr     _main
        addq.l  #8, sp
        rts

        section bss
___nstart_null:
        ds.l    1

_SysBase:
        ds.l    1

