TOP ?= ../..
PROG_AMIGA  =
PROG_AMIGA += Get_Systime
PROG_AMIGA += Simple_Timer
PROG_AMIGA += Timer_Arithmetic
# GCC generates call to memcpy() so we bring in Newlib as the last library to
# resolve. Only memcpy() is taken form libc.a.
HUNK_EXTRA  = Multiple_Timers.hunk
include $(TOP)/rules.mk
Multiple_Timers.hunk: Multiple_Timers.o
	$(LD) $(LDFLAGS_AMIGA) $^ -lc -o $@

