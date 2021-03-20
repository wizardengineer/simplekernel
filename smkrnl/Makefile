ROOTDIR.CONFIG = ../makefile.config

include $(ROOTDIR.CONFIG)

ARCHDIR   = arch/i386/
DRIVERS   = ../drivers/
SECUDIR   = ../security/
DTABLEDIR = tables/
INTERPDIR = intps/
TIMEDIR   = time/
KERNEL_INCLUDES   = -I../include
KERNEL_C_ARCH     = $(wildcard $(ARCHDIR)*.c)
KERNEL_C_FILES    = kmain.c $(KERNEL_C_ARCH)
PRINTK = printk/
#libc attributes and objects
#
LIBC = ../libc/
LIBC_INCLUDES = -I$(LIBC)include

LIBC_OBJECTS = $(LIBC)string.o $(LIBC)stdio.o

# linker
#
LDFLAGS = -T $(ARCHDIR)linker.ld -melf_i386

# kernel objects
#
DTABLES = \
	 $(DTABLEDIR)gdt.o       \
	 $(DTABLEDIR)gdt_set.o   \
	 $(DTABLEDIR)idt.o       \
	 $(DTABLEDIR)idt_set.o

SECUR_OBJECTS = \
	$(SECUDIR)smep_smap.o

INTERPS = \
	 $(INTERPDIR)exception.o     \
	 $(INTERPDIR)exception_set.o \
	 $(INTERPDIR)irqs.o	     \
	 $(INTERPDIR)irqs_set.o	     \
	 $(INTERPDIR)pic.o     	     \

KERNEL_OBJECTS = \
	 kmain.o                 \
	 $(ARCHDIR)boot.o        \
	 $(DRIVERS)vga.o         \
	 $(DRIVERS)serial_port.o \
	 $(DRIVERS)io_port.o     \
	 $(DRIVERS)keyboard.o

PRINTK_OBJECTS = \
	 $(PRINTK)printk.o

TIME_OBJECTS = \
	 $(TIMEDIR)i8254.o



#-------------------------------------------------------------------------
# Simple debug handler
# ------------------------------------------------------------------------

DEBUG_INFO = off

#ifeq($(DEBUG_INFO), 1)
#       $(CC) += -DDEBUG -ggdb
#endif

.SUFFIXES: .o .c .s .asm

all: kernel.elf

#-------------------------------------------------------------------------
# Simple rules that hold simple commands
# ------------------------------------------------------------------------

kernel.elf: kmain.o libc-compile dtables-compile security
	ld $(LDFLAGS) $(LIBC_OBJECTS) \
	   $(KERNEL_OBJECTS) \
	   $(DTABLES) $(INTERPS) $(PRINTK_OBJECTS) \
	   $(TIME_OBJECTS) $(SECUR_OBJECTS) -o kernel.elf

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

debug-run: simplekernel.iso	
	qemu-system-i386 -s -S simplekernel.iso

run: simplekernel.iso
	qemu-system-i386                                        \
		-accel tcg,thread=single                        \
		-cpu core2duo                                   \
		-m 200                                          \
		-no-reboot                                      \
		-drive format=raw,media=cdrom,file=simplekernel.iso   \
		-serial stdio                                   \
		-smp 1                                          \
		-usb                                            \
		-vga std

install:
	sudo apt install qemu-system-i386 genisoimage grub-mkrescue -y 

testing-multi:
	if [ -e "kernel.elf"  ]; then \
	    if grub-file --is-x86-multiboot kernel.elf; then \
  		echo multiboot confirmed; \
	    else \
  		echo the file is not multiboot; \
	    fi; \
	fi; \

kmain.o: drivers-compile printk-compile timer-compile
	(cd $(ARCHDIR) && make compile-arch);
	$(CC) $(CFLAGS) kmain.c -o kmain.o

security: 
	(cd $(SECUDIR) && make compile-security);

$(PRINTK)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

timer-compile: $(TIME_OBJECTS)  # Used to temporarly test a rule

$(TIMEDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

printk-compile: $(PRINTK_OBJECTS)

libc-compile:
	(cd ../libc/ && make compile-libc);

drivers-compile:
	(cd ../drivers/ && make compile-drivers);

dtables-compile:
	(cd tables/ && make compile-dtable);
	
clean:
	if [ -e "simplekernel.iso"  ]; then \
	    rm -rf *.iso;             \
	    rm -rf ..isodir/boot/simplekernel.iso; \
	fi;       		      \
	rm -rf *.o 
	rm -rf $(LIBC)*.o
	rm -rf $(ARCHDIR)*.o
	rm -rf *.elf
	rm -rf ../isodir/boot/*.elf
	rm -rf ../security/*.o
	rm -rf ../drivers/*.o
	rm -rf tables/*.o
	rm -rf intps/*.o
	rm -rf printk/*.o
	rm -rf time/*.o
