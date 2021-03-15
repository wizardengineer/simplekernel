#ifndef __KERN_PAGING_
#define __KERN_PAGING_

#include <kernel/paging.h>
#include <stdint.h>

/* Table 4-8. Format of a PAE Page-Directory-Pointer-Table Entry (PDPTE) */

typedef union _pdpte
{
  struct 
  {
    uint64_t present      : 1;
    uint64_t reserved_0   : 2;    // reversed bits that must be 0
    uint64_t page_write   : 1;    // (PWT) Page-level write-through 
    uint64_t page_cache   : 1;    // (PCD) Page-level cache disable
    uint64_t reserved_1   : 4;    // reversed bits that must be 0
    uint64_t ignored      : 3;    // Ignored
    uint64_t phys_addr    : 51;   // Physical address of 4-kbyte aligned page directory reference by entry
    uint64_t reserved_2   : 1;    // reversed bits that must be 0
  };
} pdpte_t;

#endif
