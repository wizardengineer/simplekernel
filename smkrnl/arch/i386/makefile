KERNELDIR = ../../
ROOTDIR   = ../../../
ROOTDIR.CONFIG = $(ROOTDIR)makefile.config

include $(ROOTDIR.CONFIG)

LIBC_INCLUDE = -I$(ROOTDIR)libc/include/
KERNEL_INCLUDE = -I$(KERNELDIR)include

INCLUDE = $(LIBC_INCLUDE) $(KERNEL_INCLUDE) -I.


ARCH_OBJECTS = io_port.o boot.o vga.o serial_port.o

compile-arch: $(ARCH_OBJECTS)

io_port.o:
	$(AS) $(ASFLAGS) ../../include/io/io_port.s -o io_port.o

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o
