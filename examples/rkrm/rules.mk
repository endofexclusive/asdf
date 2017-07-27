HOST             = m68k-asdf-elf
CC               = $(HOST)-gcc
AS               = asdf-vasm

ASINC            =
# Example is installed
ASINC           += -I $(TOP)/../../$(HOST)/sys-root/include_i/
# Example in repository
ASINC           += -I $(TOP)/../../opt/asdf/$(HOST)/sys-root/include_i/

ASFLAGS          =
ASFLAGS         += -quiet
ASFLAGS         += $(ASINC)
ASFLAGS         += -phxass
ASFLAGS         += -m68000
ASFLAGS         += -Fhunk
# "imported symbol <name> was not referenced"
ASFLAGS         += -nowarn=62

# Code generation options, for user
CCOPT            =
CCOPT           += -O2
CCOPT           += -mcpu=68000

CFLAGS           =
CFLAGS          += $(CCOPT)
CFLAGS          += -std=c89
CFLAGS          += -Wall
CFLAGS          += -Wextra
CFLAGS          += -pedantic
#CFLAGS          += -w

ASTARTUP         = $(TOP)/src/workbench/startup2.0/Astartup.obj

# Linker
LD              = $(CC)
# Linker flags for full CLIB applicatoin
LDFLAGS        += $(CFLAGS) -Wl,-s
# Linker flags for Commodore startup + amiga.lib. No Newlib.
LDFLAGS_AMIGA  += $(LDFLAGS) -nostdlib $(ASTARTUP) -lgcc -lamiga -lgcc

HUNK_CLIB       = $(PROG_CLIB:%=%.hunk) 
HUNK_AMIGA      = $(PROG_AMIGA:%=%.hunk) 
HUNK_ALL        = $(HUNK_CLIB) $(HUNK_AMIGA) $(HUNK_EXTRA)

all: $(PROG_FIXME) $(UNSUPPORTED) $(HUNK_ALL) $(OBJ_EXTRA)

clean:
	rm -f *.hunk *.o
	rm -f $(CLEAN_EXTRA)

$(HUNK_CLIB) : %.hunk : %.o
	$(LD) $(LDFLAGS) -o $@ $<
$(HUNK_AMIGA) : %.hunk : %.o
	$(LD) $(LDFLAGS_AMIGA) -o $@ $<
%.o : %.a
	$(AS) $(ASFLAGS) $< -o $@
%.o : %.asm
	$(AS) $(ASFLAGS) $< -o $@

### Special stuff
# Delete target if changed and its recipe exits nonzero. Used here to clean up
# vlink output files.
.DELETE_ON_ERROR:
.PHONY: $(PROG_FIXME)
.PHONY: $(UNSUPPORTED)
$(PROG_FIXME):
	@echo FIXME: $@
$(UNSUPPORTED):
	@echo UNSUPPORTED: $@

