#include <kernel/idt.h>
#include <kernel/isr.h>
#include <io/io_port.h>
#include <kernel/pic_8259.h>

/* This applies to Protected Mode:
 *   The first 0 to 7 of the ISR entries IRQ will be mapped in 
 *   the entries of IDT 8 - 15. Which is a problem considering
 *   that the first 31 entries of IDT are the ISR of exceptions.
 *   So we have to remap (changing the PICs offset) by sending 
 *   commands to the PICs (master and slave).
 * */

