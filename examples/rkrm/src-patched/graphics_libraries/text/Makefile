TOP ?= ../../..
PROG_AMIGA  =
PROG_AMIGA += cliptext
PROG_AMIGA += MeasureText
PROG_CLIB   = availfonts
# This is a font
# 1> Makedir FONTS:suits
# 1> Copy Suits8.hunk FONTS:suits/8
# 1> FixFonts
HUNK_EXTRA  = Suits8.hunk
include $(TOP)/rules.mk
Suits8.hunk: Suits8.o
	$(LD) -nostdlib $< -o $@

