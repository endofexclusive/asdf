TOP ?= ../../..
PROG_CLIB   = genlockdemo
PROG_CLIB  += UserCopperExample
PROG_CLIB  += WBClone
HUNK_EXTRA  = RGBBoxes.hunk
include $(TOP)/rules.mk
RGBBoxes.hunk: RGBBoxes.o
	$(LD) $(LDFLAGS_AMIGA) $^ -lc -o $@

