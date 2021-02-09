CODE32           equ 0x08 ; offset for setting up CS
DS_OFFSET        equ 0x10 ; 

global gdt_flush

section .text
gdt_flush:
    push ax
    lgdt [esp + 4] ; load GDT register with start address of GDT
    
    ; in order to set up our segment register CS (Code Segment)
    ; we need to do a far jump with the selector offest 0x08
    jmp CODE32:flush
flush:
    mov ax, DS_OFFSET
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; restore register
    pop ax
    retn

