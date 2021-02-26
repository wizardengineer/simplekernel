#ifndef __PIT_TIMER
#define __PIT_TIMER

/* All four PIT registers */
#define IO_COMMAND           0x36
#define IO_CMD_PORT          0x43
#define IO_CMD_SPACE(index)  (0x40 + index) /* IO space registers 40h-42h 
                                             * For PIT channel 0-2, respectively*/

#include <kernel/isr.h>
#include <kernel/idt.h>
#include <io/io_port.h>
#include <stdint.h>

void timer_install();
void timer_handler(regs ctx);

#endif
