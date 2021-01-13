include ../makefile.config

all: kernel.elf

kernel.elf: $(KERNEL_OBJECTS)
	ld $(LDFLAGS) $(KERNEL_OBJECTS) -o kernel.elf

simple.iso: kernel.elf
	cp kernel.elf ../build/iso/boot/kernel.elf
	genisoimage -R				         \
		    -b boot/grub/stage3_eltorito         \
		    -no-emul-boot		         \
		    -boot-load-size 4		         \
		    -A simple			         \
		    -input-charset utf8                  \
		    -quiet			         \
		    -boot-info-table		         \
		    -o simple.iso 			 \
		    ../build/iso

run: simple.iso
	qemu-system-i386                                        \
		-accel tcg,thread=single                        \
		-cpu core2duo                                   \
		-m 128                                          \
		-no-reboot                                      \
		-drive format=raw,media=cdrom,file=simple.iso   \
		-serial stdio                                   \
		-smp 1                                          \
		-usb                                            \
		-vga std
install:
	sudo apt install qemu-system-i386 genisoimage 

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf ../build
	rm -rf *.o kernel.elf simple.iso

