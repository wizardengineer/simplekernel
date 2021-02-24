/* The convention of our simplekernel PICs */
#ifndef __PIC_8259_HEADER_
#define __PIC_8259_HEADER_

#define PIC1            0x20          /* Master PIC IO base address*/
#define PIC2            0xA0          /* Slave PIC IO base address*/
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define PIC1_VEC_OFFSET 0x20
#define PIC2_VEC_OFFSET 0x28

#define PIC_EOI         0x20          /* End-of-Interrupt command code */

/* reinitialize the PIC controllers, giving them specified vector offsets
 * rather than 8h and 70h, as configured by default */

#define ICW1_ICW4	0x01	      /* ICW4 (not) needed */
#define ICW1_SINGLE	0x02	      /* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04	      /* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08	      /* Level triggered (edge) mode */
#define ICW1_INIT	0x10	      /* Initialization - required! */

#define ICW4_8086	0x01	      /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02	      /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	      /* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	      /* Buffered mode/master */
#define ICW4_SFNM	0x10	      /* Special fully nested (not) */

/* Headers */
#include <kernel/printk.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <io/io_port.h>
#include <string.h>
#include <stdint.h>

void pic_remap(int32_t offset1, int32_t offset2);
void pic_send_eoi(uint8_t irq);
void irq_set_mask(uint8_t irq_line);
void irq_clear_mask(uint8_t irq_line);
void pic_install();                   /* Initiate the PICs configs */

#endif
