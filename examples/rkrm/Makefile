TOP = $(abspath .)

all:
	$(MAKE) -C src TOP=$(TOP) all

clean:
	$(MAKE) -C src TOP=$(TOP) clean

matrix:
	@while true ; do \
	  $(MAKE) -C src TOP=$(TOP) clean all; \
	done

DEVS_NAME = RKRM_Devs_prgs.lha
LIBS_NAME = RKRM_Libs_prgs.lha
RKRM_URL  = http://aminet.net/dev/src/
SRCO = 

.PHONY:
bootstrap: fetch extract patch

.PHONY: fetch
fetch: $(DEVS_NAME) $(LIBS_NAME)
$(DEVS_NAME) $(LIBS_NAME):
	curl -R -O -L $(RKRM_URL)/$(DEVS_NAME)
	curl -R -O -L $(RKRM_URL)/$(LIBS_NAME)

.PHONY: extract
extract: $(DEVS_NAME) $(LIBS_NAME)
	rm -rf src-orig
	mkdir -p src-orig
	cd src-orig; lha x ../$(DEVS_NAME)
	cd src-orig; lha x ../$(LIBS_NAME)

.PHONY: patch
patch:
	cp -rv src-orig/* src-patched/
	patch -N -p1 -d src-patched < rkrm.patch

gendiff:
	diff -Naur -X rkrm.exclude src-orig src-patched > rkrm.patch || true

