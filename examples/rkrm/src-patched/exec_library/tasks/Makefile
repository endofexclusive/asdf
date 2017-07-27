TOP ?= ../../..
# Broken, probably because of calling convention of user functin given as
# CreateTask() paramter.
PROG_FIXME = simpletask
PROG_CLIB += tasklist
HUNK_EXTRA += trap.hunk
include $(TOP)/rules.mk

trap.hunk: trap_c.o trap_a.o
	$(LD) $(LDFLAGS_AMIGA) $^ -o $@

