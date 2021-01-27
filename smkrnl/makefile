ROOTDIR.CONFIG = ../makefile.config
ARCH.CONFIG = $(ARCHDIR)makefile.config

include $(ROOTDIR.CONFIG)
include 

ARCHDIR = arch/i386/
KERNEL_INCLUDES = -Iinclude/kernel/
KERNEL_C_ARCH   = $(wildcard $(ARCHDIR)*.c)
KERNEL_C_FILES    = kmain.c $(KERNEL_C_ARCH)

# linker
#
LDFLAGS = -T $(ARCHDIR)linker.ld -melf_i386

# objects
#
KERNEL_ASM_FILES = $(ARCHDIR)boot.s
KERNEL_OBJECTS =\
kmain.o \
$(ARCHDIR)boot.o \
$(ARCHDIR)vga.o

KERNEL_C_OBJECTS = kmain.o $(ARCHDIR)vga.o


.SUFFIXES: .o .c .s

all: kernel.elf

kernel.elf: kmain.o 
	ld $(LDFLAGS) $(KERNEL_OBJECTS) -o kernel.elf

simplekernel.iso: kernel.elf
	cp kernel.elf ../isodir/boot/kernel.elf
	grub-mkrescue -o simplekernel.iso ../isodir/

genisoimage:
	genisoimage -R				         \
		    -b grub/stage2_eltorito         \
		    -no-emul-boot		         \
		    -boot-load-size 4		         \
		    -A simplekernel		         \
		    -input-charset utf8                  \
		    -quiet			         \
		    -boot-info-table		         \
		    -o simplekernel.iso ../isodir/boot

run: simplekernel.iso
	qemu-system-i386                                        \
		-accel tcg,thread=single                        \
		-cpu core2duo                                   \
		-m 128                                          \
		-no-reboot                                      \
		-drive format=raw,media=cdrom,file=simplekernel.iso   \
		-serial stdio                                   \
		-smp 1                                          \
		-usb                                            \
		-vga std
install:
	sudo apt install qemu-system-i386 genisoimage 

testing-multi:
	if [ -e "kernel.elf"  ]; then \
	    if grub-file --is-x86-multiboot kernel.elf; then \
  		echo multiboot confirmed; \
	    else \
  		echo the file is not multiboot; \
	    fi; \
	fi; \

kmain.o:
	cd $(ARCHDIR) && make compile-arch
	$(CC) $(KERNEL_INCLUDES) $(CFLAGS) kmain.c -o kmain.o
		
clean:
	if [ -e "simplekernel.iso"  ]; then \
	    rm -rf *.iso;             \
	    rm -rf ..isodir/boot/simplekernel.iso; \
	fi;       		      \
	rm -rf *.o 
	rm -rf $(ARCHDIR)*.o
	rm -rf *.elf
	rm -rf ../isodir/boot/*.elf
