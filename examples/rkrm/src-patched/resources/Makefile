TOP ?= ../..
PROG_AMIGA  =
PROG_AMIGA += Allocate_Misc
PROG_AMIGA += Get_Disk_Unit_ID
PROG_AMIGA += Query_Serial
PROG_CLIB   =
PROG_CLIB  += Get_Filesys
PROG_CLIB  += Read_Potinp
HUNK_EXTRA  = Read_BattClock
# Hook Calling convention
PROG_FIXME  = CIA_interval
HUNK_EXTRA  = Read_BattClock.hunk
include $(TOP)/rules.mk
Alloc_Misc.hunk: Alloc_Misc.o
	$(LD) -nostdlib -lamiga $^ -o $@
Read_BattClock.hunk: Read_BattClock.o
	$(LD) $(LDFLAGS_AMIGA) $^ -lc -o $@

