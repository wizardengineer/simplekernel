#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/pic_8259.h>

void pic_send_eoi(uint8_t irq)
{
  if(irq >= 8) { outb(PIC2_COMMAND, PIC_EOI); } /* If slave irqs */
  outb(PIC1_COMMAND, PIC_EOI);
}

void irq_set_mask(uint8_t irq_line) 
{
  uint16_t port;
  uint8_t value;
 
  if(irq_line < 8) 
  { 
    port = PIC1_DATA; 
  } 
  else 
  {
    port = PIC2_DATA;
    irq_line -= 8;
  }
  value = inb(port) | (1 << irq_line);
  outb(port, value);        
}

void irq_clear_mask(uint8_t irq_line) 
{
  uint16_t port;
  uint8_t value;
 
  if(irq_line < 8) 
  { 
    port = PIC1_DATA; 
  } 
  else 
  {
    port = PIC2_DATA;
    irq_line -= 8;
  }
  value = inb(port) & ~(1 << irq_line);
  outb(port, value);        
}

/* This applies to Protected Mode:
 *   The first 0 to 7 of the ISR entries IRQ will be mapped in 
 *   the entries of IDT 8 - 15. Which is a problem considering
 *   that the first 31 entries of IDT are the ISR of exceptions.
 *   So we have to remap (changing the PICs offset) by sending 
 *   commands to the PICs (master and slave).
 * */
void pic_remap(int32_t offset1, int32_t offset2)
{
  uint8_t save_mask1 = 0, save_mask2 = 0;
  save_mask1 = inb(PIC1_DATA);                /* Save states of masks */
  save_mask2 = inb(PIC2_DATA);
 
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  /* start the init sequence */
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

  outb(PIC1_DATA, offset1);                   /* Master PIC vector offset */
  outb(PIC2_DATA, offset2);                   /* Slave PIC vector offset */

  outb(PIC1_DATA, 4);                         /* Tell the Master PIC that slave PIC at IRQ2 */
  outb(PIC2_DATA, 2);                         /* Tells about the cascade identity */

  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, save_mask1);                /* restore saved masks */
  outb(PIC2_DATA, save_mask2);
}


void pic_install()
{
  pic_remap(PIC1_VEC_OFFSET, PIC2_VEC_OFFSET);
}

