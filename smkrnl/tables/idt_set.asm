global idt_flush
extern idtr

section .text
idt_flush:
    lidt [idtr]
    retn
