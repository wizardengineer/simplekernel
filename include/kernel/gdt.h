#ifndef _GDT_HEADER
#define _GDT_HEADER

// entry of GDT
#define ENTRY_NUM 3

#include <stdint.h>
#include <stddef.h>

typedef struct gdt_entry
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_install();

void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// asm function/label
extern void gdt_flush(uint32_t gdt_t);

#endif
