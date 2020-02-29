# WARNING: This script removes files in the current directory. Should be used
# with make -C

# Version Configuration
VLINK_VER       = 0.16
VASM_VER        = 1.8g
BINUTILS_VER    = 2.34
GCC_VER         = 7.5.0
NEWLIB_VER      = 3.3.0

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(patsubst %/,%,$(dir $(mkfile_path)))
HERE=$(mkfile_dir)

VURL            = http://server.owl.de/~frank/tags
VLINK_DIR       = vlink
VLINK_TAR       = vlink-${VLINK_VER}.tar.gz
VLINK_UVER      = $(shell echo $(VLINK_VER) | tr . _ )
VLINK_URL       = $(VURL)/vlink$(VLINK_UVER).tar.gz

VASM_DIR        = vasm
VASM_TAR        = vasm-${VASM_VER}.tar.gz
VASM_UVER       = $(shell echo $(VASM_VER) | tr . _ )
VASM_URL        = $(VURL)/vasm$(VASM_UVER).tar.gz

BINDIR  = binutils-$(BINUTILS_VER)
GCCDIR  = gcc-$(GCC_VER)
NEWDIR  = newlib-$(NEWLIB_VER)

GNURL   = http://ftpmirror.gnu.org/gnu
BINTAR  = $(BINDIR).tar.xz
GCCTAR  = $(GCCDIR).tar.xz

NEWURL  = ftp://sourceware.org/pub/newlib/
NEWTAR  = $(NEWDIR).tar.gz

all:
	@echo "use '$(MAKE) extdep' to fetch and extract all dependencies"

extdep: extract-all
fetch-all:      f-vlink f-vasm f-binutils f-gcc f-newlib
extract-all:    x-vlink x-vasm x-binutils x-gcc x-newlib

clean:
	rm -rf $(VLINK_DIR)
	rm -rf $(VASM_DIR)
	rm -rf $(BINDIR)
	rm -rf $(GCCDIR)
	rm -rf $(NEWDIR)

distclean:
	rm -rf $(VLINK_TAR) $(VLINK_DIR)
	rm -rf $(VASM_TAR) $(VASM_DIR)
	rm -rf $(BINTAR) $(BINDIR)
	rm -rf $(GCCTAR) $(GCCDIR)
	rm -rf $(NEWTAR) $(NEWDIR)

f-vlink: $(VLINK_TAR)
$(VLINK_TAR):
	curl -L -R $(VLINK_URL) -o $@
x-vlink: $(VLINK_TAR)
	tar xzf $<
	patch -N -p1 -d vlink < $(HERE)/vlink.patch || true

f-vasm: $(VASM_TAR)
$(VASM_TAR):
	curl -L -R $(VASM_URL) -o $@
x-vasm: $(VASM_TAR)
	tar xf $<

f-binutils: $(BINTAR)
$(BINTAR):
	curl -L -R $(GNURL)/binutils/$(BINTAR) -o $@

x-binutils: $(BINTAR)
	tar xf $<

f-gcc: $(GCCTAR)
$(GCCTAR):
	curl -L -R $(GNURL)/gcc/$(GCCDIR)/$(GCCTAR) -o $@

x-gcc: $(GCCTAR)
	tar xf $<
	tar -C gcc-replace -c -O . | tar -C $(GCCDIR) -x -v


f-newlib: $(NEWTAR)
$(NEWTAR):
	curl -L -R $(NEWURL)/$(NEWTAR) -o $@

x-newlib: $(NEWTAR)
	tar xf $<
	tar -C newlib-replace -c -O . | tar -C $(NEWDIR) -x -v

