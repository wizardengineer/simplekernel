KERNELDIR = ../../
ROOTDIR   = ../../../
ROOTDIR.CONFIG = $(ROOTDIR)makefile.config

include $(ROOTDIR.CONFIG)

ARCH_OBJECTS = boot.o vga.o

compile-arch: $(ARCH_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o
