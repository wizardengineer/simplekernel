; Hardware Interrupts
%macro _macro_irq 2
global irq%1
irq%1:
    cli
    push byte 0 ; Dummy code
    push byte %2
    jmp irq_common_stub
%endmacro

extern irq_handler

section .text
align 4

irq_common_stub:
    pusha
    push ds
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

_macro_irq 0, 32
_macro_irq 1, 33
_macro_irq 2, 34
_macro_irq 3, 35
_macro_irq 4, 36
_macro_irq 5, 37
_macro_irq 6, 38
_macro_irq 7, 39
_macro_irq 8, 40
_macro_irq 9, 41
_macro_irq 10, 42
_macro_irq 11, 43
_macro_irq 12, 44
_macro_irq 13, 45
_macro_irq 14, 46
_macro_irq 15, 47



