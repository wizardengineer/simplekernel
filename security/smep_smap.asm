CPUID_SMEP          equ 7
CPUID_SMAP          equ 20
CPU_CR4_SMEP_BIT    equ 20
CPU_CR4_SMAP_BIT    equ 21

; Externs
extern serial_print

global supervisor_protection_init

section .text
align 4
supervisor_protection_init:
    push eax
    push ebx
    push ecx
    push edx
    

    mov eax, 7
    mov ecx, 0
    
    cpuid

    test ebx, CPUID_SMAP ; SMAP was implement 7 after the years SMEP, 
                         ; So if it's not supported. I won't be enabling both

    jz .worked           ; jz == je
    jmp .not_worked

.worked:
    push smap_msg
    call serial_print
    add esp, smap_len
    mov eax, cr4
    bts eax, CPU_CR4_SMEP_BIT
    mov cr4, eax

    push smep_msg
    call serial_print
    add esp, smep_len
    mov eax, cr4
    bts eax, CPU_CR4_SMEP_BIT
    mov cr4, eax
    jmp .leave

.not_worked:
    push smap_err
    call serial_print
    add esp, smap_len

    push smep_err
    call serial_print
    add esp, smep_len
    jmp .leave
    
.leave:
    ; restoring registers
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret

section .data
align 4

; SMEP datas
smep_msg db "SMEP is enable "
smep_err db "SMEP is not found "

smep_len equ $-smep_msg

; SMAP datas
smap_msg db "SMAP is enable "
smap_err db "SMAP is not found "

smap_len equ $-smap_msg

