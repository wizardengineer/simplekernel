; Hardware Interrupts
%macro _macro_irq 2
global irq%1
irq%1:
    push byte 0 ; Dummy code
    push byte %2
    jmp irq_common_stub
%endmacro

section .text
align 4


