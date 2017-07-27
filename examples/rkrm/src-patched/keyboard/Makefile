TOP ?= ../..
PROG_AMIGA  =
PROG_AMIGA += Keyboard_Events
PROG_AMIGA += Read_Keyboard_Matrix
HUNK_EXTRA  = Key_Reset.hunk
include $(TOP)/rules.mk
Key_Reset.hunk: Key_Reset.o Keyhandler.o
	$(LD) $(LDFLAGS_AMIGA) $^ -o $@

