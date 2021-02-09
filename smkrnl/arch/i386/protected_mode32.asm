; this hex value will enable protected mode and paging by 
; overwriting the first (PE aka Protected Mode Enable) and 
; last (PG aka Paging) bit of the cr0 register.
; 
; @PRME abbreviation stands for Protected Mode
; @PAGE is just Paging that's going to be enable
ENABLE_PRME_PAGE equ 0x80000001 
CODE32           equ 0x08 ; offset for setting up CS
DS_OFFSET        equ 0x10 ; 

global _PrModeInit

section .text
_PrModeInit:
    cli
    push ebx
    push ecx
    push eax
    lgdt [gdtr] ; load GDT register with start address of GDT
    
    ; enable protected mode and paging by setting the PE (Protection Enable) bit
    ; and PG (Paging) bit, respectively.
    mov ebx, cr0
    or ebx, ENABLE_PRME_PAGE
    mov cr0, ebx
    
    ; in order to set up our segment register CS (Code Segment)
    ; we need to do a far jump with the selector offest 0x08
    jmp CODE32:PrMain
PrMain:
    mov ax, DS_OFFSET
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; restore registers
    pop eax
    pop ecx
    pop ebx
    retn
