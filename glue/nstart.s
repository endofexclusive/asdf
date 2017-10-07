; nano start
; Fast and simple for applications not using the C standard library. SysBase is
; initialized. All other AmigaOS libraries have to be opened by the user.

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

; DOS return code is d0 interpreted as a LONG. If main() was compiled with
; 16-bit integers then we need to sign extend its return value.
        ifd NSTART_MSHORT
                ext.l   d0
        endif

        rts

        section bss
___nstart_null:
        ds.l    1

_SysBase:
        ds.l    1

