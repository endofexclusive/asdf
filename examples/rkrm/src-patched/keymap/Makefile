TOP ?= ../..
PROG_AMIGA  =
PROG_AMIGA += mapansi
HUNK_EXTRA  = maprawkey.hunk
OBJ_EXTRA   = appkeymap.o
# This is a key map
# Assembly uses non-explicit comments
# Did not get it to work with C:SetKeyboard
PROG_FIXME  = d.hunk
include $(TOP)/rules.mk
maprawkey.hunk: maprawkey.o
	$(LD) $(LDFLAGS_AMIGA) $^ -lc -o $@

