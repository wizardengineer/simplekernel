// entry of GDT
#include <stdint.h>
#include <stddef.h>
#include <kernel/gdt.h>
#include <kernel/printk.h>
#include <io/serial_port.h>


gdt_ptr_t gdtr;

gdt_entry_t gdt_entrys[ENTRY_NUM];

void gdt_install()
{
#if defined(__KERN_DEBUG)
  serial_print(KERN_DEBUG "GDT Trying to start. %s\n", __func__);
#endif

  printk(KERN_INFO "Kernel GDT started the loading at address -> %x\n", gdt_install);
  gdtr.limit = (sizeof(gdt_entrys) * ENTRY_NUM) - 1;
  gdtr.base = (uint32_t) (&gdt_entrys);

  
  // Null descriptor for the process memory protection
  gdt_set_entry(0, 0, 0, 0, 0);


  /* Kernel code segment descriptor, Access Value (9A = 1 00 1 1 0 1 0)
   *    P =        1  (Present)
   *    DPL =     00  (Descriptor Privilege Level: 00 denotes ring 0)
   *    Always 1 = 1  (Detemines whether or not the Descriptor is set)   
   *    Type =     1  (Type: If set to 1 then Code Segment, otherwise it's Data Segment)
   *    C =        0  (Conforming: Can be executed by ring lower or equal to DPL)
   *    R =        1  (Readable: Says that CS is readable)
   *
  */
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  /* Kernel data segment descriptor, Accesss Value (92 = 1 00 1 0 0)
   *    The only difference is that Type bit is set to 0
   *    to indicate that it's a data segment*/
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  
  gdt_flush((uint32_t) (&gdtr));
  printk(KERN_DEFAULT "\tGDT finishing loading at address -> %x\n", gdt_flush);
  printk(KERN_DEFAULT "\tGDT descriptors %x - %x\n\n", &gdt_entrys, &gdt_entrys + ENTRY_NUM);

}

void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
  // Setting the descriptor base address
  gdt_entrys[num].base_low = (base & 0xFFFF);
  gdt_entrys[num].base_middle = (base >> 16) & 0xFF;
  gdt_entrys[num].base_high = (base >> 24) & 0xFF;

  // Setting up the limit of the descriptor
  gdt_entrys[num].limit_low = (limit & 0xFFFF);
  gdt_entrys[num].granularity = (limit >> 16) & 0xFF;


  // Finally, set up the granularity and access flags
  gdt_entrys[num].granularity |= (gran & 0xF0);
  gdt_entrys[num].access = access;

}
