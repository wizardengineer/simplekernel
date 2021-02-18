; Exceptions without error codes
%macro _macro_exception_noerr 1
global  isr%1
isr%1:
    push byte 0 ; Dummy error code 
    push byte %1
    jmp isr_common_stub
%endmacro

; Exceptions with error codes
%macro _macro_exception_err 1
global  isr%1
isr%1:
    push byte %1
    jmp isr_common_stub
%endmacro


section .data
align 4
    debug_message db "Stub starting", 13
    msg_len equ $-debug_message

; you can find this in the exception.c

extern fault_handler

section .text
align 4

; simple print for debugging
extern serial_print

_print: 
    sub esp, msg_len
    push debug_message
    call serial_print
    add esp, msg_len
    ret

; ISR stub that saves the state of the CPU, sets up 
; the kernel mode segment registers, and call a C-code handler
; then restores the state of the CPU
isr_common_stub:
;    call _print
    pusha 
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10 ; loading the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax 
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8 ; cleans up the stack
    sti
    iret ; pops 5 things at the same time; CS, EFLAG, SS, ESP, EIP

_macro_exception_noerr 0 ; 0: Division By Zero Exception

_macro_exception_noerr 1 ; 1: Debug Exception

_macro_exception_noerr 2 ; 2: Non Maskable Interrupt Exception

_macro_exception_noerr 3 ; 3: Breakpoint Exception	

_macro_exception_noerr 4 ; 4: Into Detected Overflow Exception 

_macro_exception_noerr 5 ; Out of Bounds Exception

_macro_exception_noerr 6 ; Invalid Opcode Exception

_macro_exception_noerr 7 ; No Coprocessor Exception

_macro_exception_err 8 ; Double Fault Exception

_macro_exception_noerr  9 ; Coprocessor Segment Overrun Exception

_macro_exception_err 10 ; Bad TSS Exception	

_macro_exception_err 11 ; Segment Not Present Exception

_macro_exception_err 12 ; Stack Fault Exception

_macro_exception_err 13 ; General Protection Fault Exception

_macro_exception_err 14 ; Page Fault Exception

_macro_exception_noerr 15 ; Unknown Interrupt Exception	

_macro_exception_noerr 16 ; Coprocessor Fault Exception

_macro_exception_err 17 ; Alignment Check Exception (486+)

_macro_exception_noerr 18 ; Machine Check Exception (Pentium/586+)

_macro_exception_noerr 19 ; Reserved Exceptions

_macro_exception_noerr 20 ; Reserved Exceptions

_macro_exception_noerr 21 ; Reserved Exceptions

_macro_exception_noerr 22 ; Reserved Exceptions

_macro_exception_noerr 23 ; Reserved Exceptions

_macro_exception_noerr 24 ; Reserved Exceptions

_macro_exception_noerr 25 ; Reserved Exceptions

_macro_exception_noerr 26 ; Reserved Exceptions

_macro_exception_noerr 27 ; Reserved Exceptions

_macro_exception_noerr 28 ; Reserved Exceptions

_macro_exception_noerr 29 ; Reserved Exceptions

_macro_exception_noerr 30 ; Reserved Exceptions

_macro_exception_noerr 31 ; Reserved Exceptions
