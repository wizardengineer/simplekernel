global idt_flush

section .text
idt_flush:
    push eax
    mov eax, [esp + 4]
    lidt [eax]
    
    ; restore registers
    pop eax
    retn
