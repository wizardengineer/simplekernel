#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/pic_8259.h>

static void* irq_routines[16] = { NULL };

void irq_install_handler(uint8_t irq_line, irq_handlers handler)
{
  irq_routines[irq_line] = handler;
}

void irq_uninstall_handler(uint8_t irq_line)
{
  irq_routines[irq_line] = 0;
}

void irq_interrupt_handler(regs ctx)
{
  irq_handlers current_handler;
  uint8_t irq_num = ctx.int_no - 32;

  current_handler = irq_routines[irq_num];
  if(current_handler)
  {
    current_handler(ctx);
  }

  /* If the IRQ is greater than 40 (meaning it's a slave pic) 
   * then we need ot EOI ( The completion of an interrupt) to 
   * the slave controller*/
  pic_send_eoi(irq_num);
}
