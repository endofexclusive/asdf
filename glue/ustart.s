; micro start
; * Initializes SysBase
; * Opens dos.library and sets DOSBase
; * Initializes stdin, stdout, stderr

        include "dos/dos.i"

        xdef    ___ustart
        xdef    __exit

        section code
___ustart:
        move.l  sp, spatmain
        move.l  d0, -(sp)
        move.l  a0, -(sp)
        jsr     ___ustart_main
        addq.l  #8, sp
; If we come back here, then main() was never called.
        moveq.l #RETURN_ERROR, d0
        rts

; _exit(int status)
__exit:
        move.l  4(sp), d7
        move.l  spatmain(pc), sp
        jsr     ___ustart__exit_main
exit_noclose:
        move.l  d7, d0
        rts

spatmain:
        dc.l    0

