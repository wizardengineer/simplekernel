ROOTDIR.CONFIG = ../makefile.config

include $(ROOTDIR.CONFIG)

KERNEL_INCLUDE = -I../smkrnl/include/ 
LIBC_INCLUDE = -I../libc/include/ 
INCLUDE = $(LIBC_INCLUDE) $(KERNEL_INCLUDE)

DRIVER_OBJECTS = io_port.o vga.o serial_port.o

compile-drivers: $(DRIVER_OBJECTS)

io_port.o:
	$(AS) $(ASFLAGS) ../smkrnl/include/io/io_port.s -o io_port.o

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS)  $< -o $@
clean:
	rm -rf *.o
