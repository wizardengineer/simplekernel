#ifndef _GDT_HEADER
#define _GDT_HEADER

// entry of GDT
#define ENTRY_NUM 3

#include <stdint.h>
#include <stddef.h>

typedef union _gdt_descriptor
{
  struct
  {
    uint64_t limit_low    : 16;
    uint64_t base_low     : 16;
    uint64_t base_middle  : 8;
    uint64_t access       : 8;
    uint64_t granularity  : 8;
    uint64_t base_high    : 8;
  };
} __attribute__((packed)) gdt_entry_t;

typedef struct _gdt_ptr
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

typedef struct _tss_segment_fmt
{
  uint32_t link       : 16;
  uint32_t reserved_1 : 16;
  uint32_t esp_0      : 32;
  uint32_t ss_0       : 16;
  uint32_t reserved_2 : 16;
  uint32_t esp_1      : 32;
  uint32_t ss_1       : 16;
  uint32_t reserved_3 : 16;
  uint32_t esp2       : 32;
  uint32_t ss_2       : 16;
  uint32_t reserved_4 : 16;
  uint32_t eip        : 32;
  uint32_t eflags     : 32;
  uint32_t eax        : 32;
  uint32_t ecx        : 32;
  uint32_t edx        : 32;
  uint32_t ebx        : 32;
  uint32_t esp        : 32;
  uint32_t esi        : 32;
  uint32_t edi        : 32;
  uint32_t es         : 16;
  uint32_t reserved_5 : 16;
  uint32_t cs         : 16;
  uint32_t reserved_6 : 16;
  uint32_t ss         : 16;
  uint32_t reserved_7 : 16;
  uint32_t ds         : 16;
  uint32_t reserved_8 : 16;
  uint32_t fs         : 16;
  uint32_t reserved_9 : 16;
  uint32_t gs         : 16;
  uint32_t reserved_10: 16;
  uint32_t ldtr       : 16;
  uint32_t reserved_11: 16;
  uint32_t reserver_12: 16;
  uint32_t iopb_offset: 16;
} __attribute__((packed)) tss_segment;

void gdt_install();

void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// asm function/label
extern void gdt_flush(uint32_t gdt_t);

#endif
