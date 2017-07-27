TOP ?= ../../..
OBJ_EXTRA  =
OBJ_EXTRA += out/Astartup.o
OBJ_EXTRA += out/AWstartup.o
OBJ_EXTRA += out/Rstartup.o
OBJ_EXTRA += out/RWstartup.o
OBJ_EXTRA += out/RXstartup.o
OBJ_EXTRA += out/Qstartup.o
CLEAN_EXTRA = $(OBJ_EXTRA)
include $(TOP)/rules.mk
out:
	mkdir -p out
out/Astartup.o: startup.asm | out
	$(AS) $(ASFLAGS) -DASTARTUP=1 $^ -o $@
out/AWstartup.o: startup.asm | out
	$(AS) $(ASFLAGS) -DAWSTARTUP=1 $^ -o $@
out/Rstartup.o: startup.asm | out
	$(AS) $(ASFLAGS) -DRSTARTUP=1 $^ -o $@
out/RWstartup.o: startup.asm | out
	$(AS) $(ASFLAGS) -DRWSTARTUP=1 $^ -o $@
out/RXstartup.o: startup.asm | out
	$(AS) $(ASFLAGS) -DRXSTARTUP=1 $^ -o $@
out/Qstartup.o: startup.asm | out
	$(AS) $(ASFLAGS) -DQSTARTUP=1 $^ -o $@

