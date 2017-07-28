CC=m68k-asdf-elf-gcc

CCOPT  =
CCOPT += -O2
CCOPT += -mcpu=68000
CCOPT += -mshort

CFLAGS  =
CFLAGS += $(CCOPT)
CFLAGS += -std=gnu99
CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -pedantic
# Force compiler to reserve register a5 for CUSTOMBASE, instead of using
# compilers default addressing.
CFLAGS += -DCUSTOM_AS_GLOBAL_REG=1

LDFLAGS  =
LDFLAGS += -qnstart
LDFLAGS += -Wl,-s
# vlink -sd combines .bss and .data sections
#LDFLAGS += -Wl,-sd

NAME=takesys
all: main.s demo.s $(NAME).hunk

OBJS = main.o demo.o

demo.o: demo.c cust.h
main.o: main.c cust.h xproto.h
main.s: main.c cust.h xproto.h
%.s: %.c
	$(CC) $(CFLAGS) -fverbose-asm -S -o $@ $<

$(NAME).hunk: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(NAME).hunk *.s

