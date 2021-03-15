#ifndef _IDT_HEADER
#define _IDT_HEADER

#define IDT_ENTRY_NUM      256

#define IDT_FIRST_32_GATES 32 // Exceptions

#include <stdint.h>
#include <string.h>
#include <kernel/printk.h>
#include <static_assert.h>

/* Entrys */
typedef struct idt_entry
{
  uint16_t base_low;
  uint16_t selector;
  uint8_t  always_0;
  uint8_t  type;
  uint16_t base_high;
} __attribute((packed)) idt_entry_t;

//static_assert(sizeof(idt_entry) == 52,
//              "IDT Gate fmt size does not match");

/* Pointer to entry */
typedef struct idt_ptr
{
  uint16_t limit;
  uint32_t base;
} __attribute((packed)) idt_ptr_t;
//static_assert(sizeof(idt_ptr_t) == 48,
//              "IDTR fmt size does not match");


void idt_set_gate(uint8_t num, 
                  uint32_t base, 
                  uint16_t sel, 
                  uint8_t flags);

void idt_install();

/* Extern asm function */
extern void idt_flush();

#endif
