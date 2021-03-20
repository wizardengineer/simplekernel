; Constants for the multiboot header
MBALIGN equ 1 << 0            ; align loaded modules on page
MEMINFO equ 1 << 1            ; provide memory map
FLAGS   equ MBALIGN | MEMINFO ; multibootloader 'flag' field
MAGIC   equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

; Early extern
extern terminal_initialize
extern _simple_banner
extern _end_banner
extern gdt_install ; you'll be missed
extern paging_on   ; memory segmentation replacement
extern idt_install
extern kmain

; Other externs
extern timer_install
extern keyboard_install


; Setting the standards for the multiboot header to mark this
; as the kernel.
section .multiboot
align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

; Multiboot standard does not create a stack, so there won't be
; esp or anything of the sorts. It's up to the kernel to create 
; the stack.

; Size of stack
; KERNEL_STACK equ 4096
section .bss
align 16
stack_bottom:
   resb 16384
stack_top:

; The linker script will specify the entry of the kernel, in our
; case that would be _start. 
section .text
global _start:function (_start.end - _start)
_start:
	; The bootloader has loaded us into 32-bit protected mode on a x86
	; machine. Interrupts are disabled. Paging is disabled. The processor
	; state is as defined in the multiboot standard. The kernel has full
	; control of the CPU. The kernel can only make use of hardware features
	; and any code it provides as part of itself. 
        ; Jump to the os
        mov eax, 0xCAFEBABE

	; To set up a stack, we set the esp register to point to the top of our
	; stack (as it grows downwards on x86 systems). This is necessarily done
	; in assembly as languages such as C cannot function without a stack.
	mov esp, stack_top

        ; Setting up the Framebuffer and small banner
        call terminal_initialize
        call _simple_banner

 	; This is a good place to initialize crucial processor state before the
	; high-level kernel is entered.The GDT should be loaded here. Paging should
        ; be enabled here.
	; C++ features such as global constructors and exceptions will require
	; runtime support to work as well.
        
        call gdt_install ; -> goodbye ;(
        ; call paging_on
        call idt_install

        call timer_install
        call keyboard_install

        ; End of banner
        call _end_banner

	; Enter the high-level kernel. The ABI requires the stack is 16-byte
	; aligned at the time of the call instruction (which afterwards pushes
	; the return pointer of size 4 bytes). 	extern kmain
	call kmain

	; If the system has nothing more to do, put the computer into an
	; infinite loop. To do that:
	; 1) Disable interrupts with cli (clear interrupt enable in eflags).
	;    They are already disabled by the bootloader, so this is not needed.
	;    Mind that you might later enable interrupts and return from
	;    kernel_main (which is sort of nonsensical to do).
	; 2) Wait for the next interrupt to arrive with hlt (halt instruction).
	;    Since they are disabled, this will lock up the computer.
	; 3) Jump to the hlt instruction if it ever wakes up due to a
	;    non-maskable interrupt occurring or due to system management mode.
	cli
.hang:	
        hlt
	jmp .hang
.end:


    
