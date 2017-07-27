TOP ?= ../..
PROG_AMIGA = Speak_Narrator
HUNK_EXTRA = Full_Narrator.hunk
include $(TOP)/rules.mk
Full_Narrator.hunk: Full_Narrator.o
	$(LD) $(LDFLAGS_AMIGA) -lc $^ -o $@

