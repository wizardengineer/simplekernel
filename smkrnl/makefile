include ../makefile.config

ARCHDIR = arch/i386/

KERNEL_C_ARCH = $(wildcard $(ARCHDIR)*.c)
KERNEL_ALL_C  = kmain.c # $(KERNEL_C_ARCH)

# linker
#
LDFLAGS = -T $(ARCHDIR)linker.ld -melf_i386

# objects
#
KERNEL_ASM_FILES = $(ARCHDIR)boot.s
KERNEL_OBJECTS = kmain.o boot.o

all: kernel.elf

kernel.elf: $(KERNEL_OBJECTS)
	ld $(LDFLAGS) $(KERNEL_OBJECTS) -o kernel.elf

simplekernel.iso: kernel.elf
	cp kernel.elf ../isodir/boot/kernel.elf
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

kmain.o: $(KERNEL_ALL_C)
	$(CC) $(CFLAGS) $(KERNEL_ALL_C) -o kmain.o

boot.o: $(KERNEL_ASM_FILES)
	$(AS) $(ASFLAGS) $(KERNEL_ASM_FILES) -o boot.o

clean:
	if [ -e "simplekernel.iso"  ]; then \
	    rm -rf *.iso;             \
	    rm -rf ..isodir/boot/simplekernel.iso; \
	fi;       		      \
	rm -rf *.o 
	rm -rf $(ARCHDIR)*.o
	rm -rf *.elf
	rm -rf ../isodir/boot/*.elf
