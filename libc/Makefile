ROOTDIR = ../
ROOTDIR.CONFIG = $(ROOTDIR)makefile.config
INCLUDE_LIBC = -Iinclude/
INCLUDE_KERNEL = -I../include/

include $(ROOTDIR.CONFIG)

LIBC_OBJECTS = string.o stdio.o

.SUFFIXES: .o .c

compile-libc: $(LIBC_OBJECTS)

%.o: %.c
	$(CC) $(INCLUDE_LIBC) $(INCLUDE_KERNEL) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
