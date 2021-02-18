KERNELDIR = ../../
ROOTDIR   = ../../../
ROOTDIR.CONFIG = $(ROOTDIR)makefile.config

include $(ROOTDIR.CONFIG)

LIBC_INCLUDE = -I$(ROOTDIR)libc/include/
KERNEL_INCLUDE = -I$(ROOTDIR)include

INCLUDE = $(LIBC_INCLUDE) $(KERNEL_INCLUDE) -I.

ARCH_OBJECTS = boot.o 

compile-arch: $(ARCH_OBJECTS)

# IDK if I'm going to put much C files in this folder
%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o
