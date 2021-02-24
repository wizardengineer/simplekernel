ROOTDIR.CONFIG = ../../makefile.config
INTERP = ../intps/

DTABLE_OBJ = gdt.o gdt_set.o idt.o idt_set.o
INTERP_OBJ = $(INTERP)exception.o $(INTERP)exception_set.o \
	     $(INTERP)irqs.o $(INTERP)irqs_set.o $(INTERP)pic.o

include $(ROOTDIR.CONFIG)

compile-dtable: $(DTABLE_OBJ) $(INTERP_OBJ)

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

$(INTERP)/%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

$(INTERP)/%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@


clean:
	rm -rf *.o
