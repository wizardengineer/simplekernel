ROOTDIR.CONFIG = ../../makefile.config
KERNELDIR = ../
ROOTDIR   = ../../

LIBC_INCLUDE = -I$(ROOTDIR)libc/include/
KERNEL_INCLUDE = -I$(KERNELDIR)include

INCLUDE = $(LIBC_INCLUDE) $(KERNEL_INCLUDE) -I.

DTABLE_OBJ = gdt.o gdt_set.o

include $(ROOTDIR.CONFIG)

compile-dtable: $(DTABLE_OBJ)

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o
