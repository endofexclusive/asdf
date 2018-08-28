LUAVER = 5.3.4
LUASRC = ext/lua-$(LUAVER)/src/
LUATESTS = ext/lua-$(LUAVER)-tests/
LIBLUA = $(LUASRC)/liblua.a

CCOPT  = -O3
CCOPT += -mcpu=68020

HOST=m68k-asdf-elf-
CC=$(HOST)gcc
CFLAGS  =
CFLAGS += $(CCOPT)
CFLAGS += -std=c99
#CFLAGS += -std=c89
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -DLUA_32BITS
CFLAGS += -I$(LUASRC)
LUACFLAGS = $(CFLAGS)

.PHONY: all
all: ami-lua.hunk luac.hunk

ami-lua.c: $(LUASRC)/lua.c
	cp $< $@
	patch < ami-lua.patch

ami-lua.hunk: ami-lua.c $(LIBLUA)
	$(CC) $(CFLAGS) $^ -o $@ -lm

luac.hunk: $(LUASRC)/luac.c $(LIBLUA)
	$(CC) $(CFLAGS) $^ -o $@ -lm

liblua: $(LIBLUA)
$(LIBLUA):
	$(MAKE) -C $(LUASRC) CC="$(CC)" CFLAGS="$(LUACFLAGS)" liblua.a

.PHONY: fetch
fetch:
	mkdir -p ext
	curl -R -O http://www.lua.org/ftp/lua-$(LUAVER).tar.gz
	curl -R -O https://www.lua.org/tests/lua-$(LUAVER)-tests.tar.gz
	tar xzf lua-$(LUAVER).tar.gz -C ext
	tar xzf lua-$(LUAVER)-tests.tar.gz -C ext

.PHONY: clean
clean:
	@if [ -x $(LUASRC) ]; then \
	  $(MAKE) -C $(LUASRC) CC="$(CC)" CFLAGS="$(LUACFLAGS)" clean; \
	fi
	rm -f *.hunk
	rm -f *.o

.PHONY: distclean
distclean: clean
	rm -f ami-lua.c
	rm -rf ext

