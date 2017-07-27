TOP ?= ../..
HUNK_EXTRA = ramdev.device.hunk
include $(TOP)/rules.mk
ramdev.device.hunk: ramdev.device.o
	$(LD) -Wl,-s,-sc -nostdlib -lamiga $^ -o $@

