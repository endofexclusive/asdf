TOP ?= ../../..
PROG_AMIGA  = timersoftint
HUNK_EXTRA  = vertb.hunk rbf.hunk
#PROG_FIXME = rbf
include $(TOP)/rules.mk

vertb.hunk: vertb.o vertbserver.o
	$(LD) $(LDFLAGS_AMIGA) $^ -o $@
rbf.hunk: rbf.o rbfhandler.o
	$(LD) $(LDFLAGS) $^ -o $@

