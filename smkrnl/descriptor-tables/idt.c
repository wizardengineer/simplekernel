#include <kernel/idt.h>
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
  idt_gates[num].type = flags;
  idt_gates[num].always_0 = 0;

}

void idt_install()
{
  // Setting speical IDT pointer
  idtr.limit = (sizeof(idt_entry_t) * 256 ) - 1;
  idtr.base = (uint32_t)(&idt_gates);

  // Clearing out the entire entries of out 'idt_gates'
  memset(&idt_gates, 0, sizeof(idt_entry_t) * 256);

  // Setting up the ISRs

  // Loading the ldtr
  idt_flush((uint32_t) (&idtr));
}
