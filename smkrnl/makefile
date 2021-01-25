include ../makefile.config

ARCHDIR = arch/i386/

KERNEL_C_ARCH = $(wildcard $(ARCHDIR)*.c)
KERNEL_ALL_C  = kmain.c # $(KERNEL_C_ARCH)

# linker
#
LDFLAGS = -T $(ARCHDIR)link.ld -melf_i386

# objects
#
KERNEL_ASM_FILES = $(ARCHDIR)boot.s
KERNEL_OBJECTS = kmain.o $(ARCHDIR)boot.o

all: kernel.elf

kernel.elf: $(KERNEL_OBJECTS)
	ld $(LDFLAGS) $(KERNEL_OBJECTS) -o kernel.elf

simple.iso: kernel.elf
	cp kernel.elf ../grub/boot/kernel.elf
	genisoimage -R				         \
		    -b ../grub/boot/stage3_eltorito      \
		    -no-emul-boot		         \
		    -boot-load-size 4		         \
		    -A simple			         \
		    -input-charset utf8                  \
		    -quiet			         \
		    -boot-info-table		         \
		    -o simple.iso 			 \
		    ../grub/

run: simple.iso
	qemu-system-i386                                        \
		-accel tcg,thread=single                        \
		-cpu core2duo                                   \
		-m 128                                          \
		-no-reboot                                      \
		-drive format=raw,media=cdrom,file=../grub/simple.iso   \
		-serial stdio                                   \
		-smp 1                                          \
		-usb                                            \
		-vga std
install:
	sudo apt install qemu-system-i386 genisoimage 

kmain.o: $(KERNEL_ALL_C)
	$(CC) $(CFLAGS) $(KERNEL_ALL_C) -o kmain.o

arch/i386/boot.o: $(KERNEL_ASM_FILES)
	$(AS) $(ASFLAGS) $(KERNEL_ASM_FILES) -o boot.o

clean:
	rm -rf *.o 
	rm -rf $(ARCHDIR)*.o

