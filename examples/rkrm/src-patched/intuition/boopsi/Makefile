TOP ?= ../../..
PROG_AMIGA  =
PROG_AMIGA += Talk2boopsi
PROG_AMIGA += RKMButClass
HUNK_EXTRA += userkmmodel.hunk
include $(TOP)/rules.mk
userkmmodel.hunk: userkmmodel.o RKMModel.o
	$(LD) $(LDFLAGS_AMIGA) $^ -o $@
