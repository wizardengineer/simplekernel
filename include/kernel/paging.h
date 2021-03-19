#ifndef __KERN_PAGING_
#define __KERN_PAGING_

#include <stdint.h>

/* Table 4-8. Format of a PAE Page-Directory-Pointer-Table Entry (PDPTE) */

typedef union _pdpte
{
  struct 
  {
    uint64_t present      : 1;    // Present; must be 1 to reference a page directory
    uint64_t reserved_0   : 2;    // reversed bits that must be 0
    uint64_t page_write   : 1;    // (PWT) Page-level write-through 
    uint64_t page_cache   : 1;    // (PCD) Page-level cache disable
    uint64_t reserved_1   : 4;    // reversed bits that must be 0
    uint64_t ignored      : 3;    // Ignored
    uint64_t phys_addr    : 51;   // Physical address of 4-kbyte aligned page directory reference by entry
    uint64_t reserved_2   : 1;    // reversed bits that must be 0
  };
}__attribute__((packed)) pdpte_t, *ppdpte_t;

/* Table 4-10. Format of a PAE Page-Directory Entry that References a Page Table */

typedef union _pde
{
  struct 
  {
    uint64_t present      : 1;    // Present; must be 1 to reference a page table
    uint64_t read_write   : 1;    // Read/write; if 0, writes may not be allowed to the 2-MByte region controlled by this entry
    uint64_t supervisor   : 1;    // Superviosr; if 0, usermode won't have access to 2mb region controlled by this entry
    uint64_t page_write   : 1;    // (PWT) Page-level write-through
    uint64_t page_cache   : 1;    // (PCD) Page-level cache-disable
    uint64_t access       : 1;    // (A) Acessed; indicate if entry has been used for linear address translation
    uint64_t ignored_0    : 1;    // Ignored
    uint64_t page_size    : 1;    // (PS) Page size, if 0 page size will be 4kb or else it'll be 2mb
    uint64_t ignored_1    : 4;    // Ignored
    uint64_t phys_addr    : 50;   // Physical address of 4-KByte aligned page table referenced by this entry
    uint64_t reversed_0   : 1;    // Reserved (must be 0)

    uint64_t nxe          : 1;    /* If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from 
                                    the 2-MByte region controlled by this entry; see Section 4.6); otherwise, reserved (must 
                                    be 0) */
  };
}__attribute__((packed)) pde_t, *ppde_t;

/* Table 4-11. Format of a PAE Page-Table Entry that Maps a 4-KByte Page */

typedef union _pte
{
  struct 
  {
    uint64_t present     : 1;    // Present; must be 1 to map a 4-KByte page
    uint64_t read_write  : 1;    // Read/write; if 0, writes may not be allowed to the 4-KByte page referenced by this entry
    uint64_t supervisor  : 1;    // Supervisor; if 0, usermode won't have access to the 4KByte page referenced by this entry
    uint64_t page_write  : 1;    // (PWT) Page-level write-through
    uint64_t page_cache  : 1;    // (PCD) Page-level cache-disable
    uint64_t access      : 1;    // Accessed; indicates whether software has accessed the 4kb page referenced by this entry
    uint64_t dirty       : 1;    // Dirty; indicates whether software has written to the 4-KByte page referenced by this entry
    uint64_t pat         : 1;    // If supported, indirectly determines the memory type used to access the 4KB page referenced by this entry
    uint64_t global      : 1;    // Global; if CR4.PGE = 1, determines whether the translation is global; ignored otherwise
    uint64_t ignored_0   : 3;    // Ignored
    uint64_t phys_addr   : 50;   // Physical address of the 4-KByte page referenced by this entry
    uint64_t reserved_0  : 1;    // Reserved (must be 0)
    uint64_t nxe         : 1;    /*  If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 
                                    4-KByte page controlled by this entry; see Section 4.6); otherwise, reserved (must be 0) */
  };
}__attribute__((packed)) pte_t, *ppte_t;

pdpte_t pdpt[4]   __attribute__((aligned(0x20)));
pde_t   pdt[512]  __attribute__((aligned(0x1000)));
pte_t   pt[512]   __attribute__((aligned(0x1000)));

extern void paging_on();

void paging_install();

void* get_physaddr(void* virtualaddr);

void map_page(void* physaddr, void* virtualaddr, uint32_t flags);

#endif
