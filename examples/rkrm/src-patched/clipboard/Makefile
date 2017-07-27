TOP ?= ../..
HUNK_EXTRA  = clipdemo.hunk
HUNK_EXTRA += changehook_test.hunk
include $(TOP)/rules.mk
clipdemo.hunk: cbio.o clipdemo.o
	$(LD) $(LDFLAGS) $^ -o $@
changehook_test.hunk: cbio.o hookface.o changehook_test.o
	$(LD) $(LDFLAGS) $^ -o $@

