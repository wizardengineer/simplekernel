ROOTDIR = ../
ROOTDIR.CONFIG = $(ROOTDIR)makefile.config
INCLUDE_LIBC = -Iinclude/

include $(ROOTDIR.CONFIG)

LIBC_OBJECTS = string.o

.SUFFIXES: .o .c

compile-libc: $(LIBC_OBJECTS)

%.o: %.c
	$(CC) $(INCLUDE_LIBC) $(CFLAGS)  $< -o $@

clean:
	rm -rf *.o
