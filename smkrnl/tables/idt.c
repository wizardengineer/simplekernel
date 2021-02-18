#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/printk.h>
#include <string.h>

idt_ptr_t idtr;
idt_entry_t idt_gates[IDT_ENTRY_NUM];

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  // Setting the base address
  idt_gates[num].base_low = (base & 0xffff);
  idt_gates[num].base_high = (base >> 16) & 0xffff;

  // Setting the selector and flags (type)
  idt_gates[num].selector = sel;
  idt_gates[num].type = flags | 0x60;
  idt_gates[num].always_0 = 0;

}

void idt_install()
{

  // Clearing out the entire entries of out 'idt_gates'
  memset(&idt_gates, 0, sizeof(idt_entry_t) * 256);

  // Setting speical IDT pointer
  idtr.limit = (sizeof(idt_entry_t) * 256 ) - 1;
  idtr.base = (uint32_t)(&idt_gates);

#if defined(__KERN_DEBUG)
  serial_print(KERN_DEBUG "IDT starting\n");
#endif
  
  printk(KERN_INFO "Kernel IDT started the loading at address -> %x\n", &idt_install);
  // Setting up the ISRs
  idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
  idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
  idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
  idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
  idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
  idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
  idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
  idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
  idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
  idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
  idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
  idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
  idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
  idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
  idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
  idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
  idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
  idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
  idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
  idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
  idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
  idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
  idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
  idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
  idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
  idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
  idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
  idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
  idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
  idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
  idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
  idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);

#if defined(__KERN_DEBUG)
  serial_print("Finish loading all 32 Exceptions in IDT entries\n");
#endif

  // Loading the ldtr
  idt_flush();
  asm volatile("sti"); // not needed

  printk(KERN_DEFAULT "\tIDT finising loading at address -> %x\n", idt_flush);
  printk(KERN_DEFAULT "\tIDT descriptors %x - %x\n\n", &idt_gates, &idt_gates + IDT_ENTRY_NUM);
#if defined(__KERN_DEBUG)
  serial_print("Finish loading the IDTR\n");
#endif
}
