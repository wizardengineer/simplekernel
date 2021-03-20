ROOTDIR.CONFIG = ../makefile.config

include $(ROOTDIR.CONFIG)

SECUR_OBJECTS = smep_smap.o

compile-security: $(SECUR_OBJECTS)

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@ 
