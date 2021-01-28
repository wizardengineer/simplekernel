KERNELDIR = ../../
ROOTDIR   = ../../../
ROOTDIR.CONFIG = $(ROOTDIR)makefile.config

include $(ROOTDIR.CONFIG)

LIBC_INCLUDE = -I$(ROOTDIR)libc/include/
KERNEL_INCLUDE = -I$(KERNELDIR)include

INCUDE = $(LIBC_INCLUDE) $(KERNEL_INCLUDE)

ARCH_OBJECTS = boot.o vga.o

compile-arch: $(ARCH_OBJECTS)

%.o: %.c
	$(CC) $(LIBC_INCLUDE) $(KERNEL_INCLUDE) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o
