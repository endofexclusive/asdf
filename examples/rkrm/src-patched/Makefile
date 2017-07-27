TOP ?= $(abspath ..)
SUBDIRS = $(sort $(shell find * -type d))

all:
	@for d in $(SUBDIRS) ; do \
	  $(MAKE) -C $$d TOP=$(TOP) all || exit 1; \
	done

clean:
	@for d in $(SUBDIRS) ; do \
	  $(MAKE) -C $$d TOP=$(TOP) clean || exit 1; \
	done

