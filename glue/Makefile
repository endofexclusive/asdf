OUTDIR ?= build/
INSTALLDIR ?= dist/
ifneq ($(strip $(OUTDIR)),)
  ifneq ($(strip $(OUTDIR)),$(dir $(strip $(OUTDIR))))
    override OUTDIR:=$(OUTDIR)/
  endif
endif

HOST=m68k-asdf-elf-
CC  	= $(HOST)gcc
AR	= $(HOST)ar
RANLIB 	= $(HOST)ranlib
VASM	= asdf-vasm

CFLAGS  =
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Os

VASMFLAGS  =
VASMFLAGS += -quiet
VASMFLAGS += -Fhunk
VASMFLAGS += -phxass
VASMFLAGS += $(ASMINCFLAGS)
ASMINCFLAGS = -I../ext/ndk-3.9/Include/include_i

LIBFILE = $(OUTDIR)libglue.a
STARTSRCS  =
STARTSRCS += nstart.s
STARTSRCS += ustart.s

LIBSRCS  =
LIBSRCS += calloc.c
LIBSRCS += clock.c
LIBSRCS += close.c
LIBSRCS += dynmem.c
LIBSRCS += fdnode.c
LIBSRCS += free.c
LIBSRCS += fstat.c
LIBSRCS += getpid.c
LIBSRCS += isatty.c
LIBSRCS += kill.c
LIBSRCS += lseek.c
LIBSRCS += malloc.c
LIBSRCS += open.c
LIBSRCS += read.c
LIBSRCS += realloc.c
LIBSRCS += rename.c
LIBSRCS += time.c
LIBSRCS += unlink.c
LIBSRCS += write.c

LIBSRCS += ustart_main.c

LIBOBJS := $(LIBSRCS:.c=.o)
LIBOBJS := $(LIBOBJS:.S=.o)
LIBOBJS := $(addprefix $(OUTDIR),$(LIBOBJS))

STARTOBJS := $(STARTSRCS:.s=.o)
STARTOBJS := $(addprefix $(OUTDIR),$(STARTOBJS))

.PHONY: all
all: $(LIBFILE) $(STARTOBJS)

$(LIBOBJS): dbg.h dynmem.h fdnode.h
$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OUTDIR)%.o: %.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)%.o: %.s | $(OUTDIR)
	$(VASM) $(VASMFLAGS) $< -o $@

$(LIBFILE): $(LIBOBJS)
	$(AR) cru $@ $^
	$(RANLIB) $@

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp $(LIBFILE) $(STARTOBJS) $(INSTALLDIR)

.PHONY: clean
clean:
	rm -f $(LIBOBJS)
	rm -f $(STARTOBJS)
	rm -f $(LIBFILE)
	-rmdir -p $(OUTDIR) 2> /dev/null || true

