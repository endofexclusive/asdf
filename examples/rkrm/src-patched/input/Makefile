TOP ?= ../..
PROG_AMIGA = Set_Mouse
HUNK_EXTRA = Swap_Buttons.hunk
include $(TOP)/rules.mk
Swap_Buttons.hunk: Swap_Buttons.o Inputhandler.o
	$(LD) $(LDFLAGS_AMIGA) $^ -o $@

