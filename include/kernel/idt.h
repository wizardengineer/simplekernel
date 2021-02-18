#ifndef _IDT_HEADER
#define _IDT_HEADER

#define IDT_ENTRY_NUM 256

#define IDT_FIRST_32_GATES 32 // Exceptions

#include <stdint.h>
#include <string.h>

// Entrys
typedef struct idt_entry
{
  uint16_t base_low;
  uint16_t selector;
  uint8_t  always_0;
  uint8_t  type;
  uint16_t base_high;
} __attribute((packed)) idt_entry_t;

// Pointer to entry
typedef struct idt_ptr
{
  uint16_t limit;
  uint32_t base;
} __attribute((packed)) idt_ptr_t;

void idt_set_gate(uint8_t num, 
                  uint32_t base, 
                  uint16_t sel, 
                  uint8_t flags);

void idt_install();

// Extern asm function
extern void idt_flush();

#endif
