; Enables paging in CR0.PG
PAGING_ON equ 0x8000000

; externs
extern printk
extern pdpt

global paging_on

section .text
align 4

paging_on:
;    push msg
;    call printk
;    add esp, msg_l
    push eax
    push ebx

; Enabling PAE
    mov ebx, cr4
    bts ebx, 5
    mov cr4, ebx
    
    xor ebx, ebx ; Just to be safe
    mov ebx, pdpt
    mov cr3, ebx


; Enabling paging
    mov eax, cr0 
    or eax, PAGING_ON
    mov cr0, eax
    
    pop ebx
    pop eax
    retn

section .data
align 4
    msg db "[+] paging is on ...\n", 20     ; msg 
    msg_l equ $-msg                         ; msg length
