ROOTDIR.CONFIG = ../makefile.config

include $(ROOTDIR.CONFIG)

KERNEL_INCLUDE = -I../include/ 
LIBC_INCLUDE = -I../libc/include/ 
INCLUDE = $(LIBC_INCLUDE) $(KERNEL_INCLUDE)

DRIVER_OBJECTS = io_port.o vga.o serial_port.o keyboard.o

compile-drivers: $(DRIVER_OBJECTS)

io_port.o:
	$(AS) $(ASFLAGS) ../include/io/io_port.s -o io_port.o

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS)  $< -o $@
clean:
	rm -rf *.o
