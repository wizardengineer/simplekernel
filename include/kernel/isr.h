#ifndef __ISR_HEADER_
#define __ISR_HEADER_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <io/serial_port.h>
#include <kernel/printk.h>
#include <kernel/pic_8259.h>
#include <kernel/idt.h>


typedef struct registers
{
  uint32_t gs, 
           fs, 
           es, 
           ds;

  uint32_t edi, 
           esi, 
           ebp, 
           esp, 
           ebx, 
           edx, 
           ecx, 
           eax;

  uint32_t int_no, 
           err_code;

  uint32_t eip, 
           cs, 
           eflags, 
           useresp, 
           ss;
} __attribute((packed)) regs, *p_regs;

const char *exception_messages[IDT_FIRST_32_GATES];

/* IRQ custom handler */
typedef void(*irq_handlers)(regs r);

void irq_interrupt_handler(regs r);

void irq_install_handler(uint8_t irq_line, irq_handlers handler);

void irq_uninstall_handler(uint8_t irq_line);

/* Fault handler */
void fault_handler(regs registers);

/* You can find in exception_set.asm */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* Hardware Interrupts */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif
