#include <kernel/printk.h>
#include <kernel/pit_i8254.h>
#include <kernel/isr.h>
#include <kernel/idt.h>
#include <io/io_port.h>
#include <stdint.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* This will keep track of how many ticks
 * the system ran*/
static uint32_t ticks = 0;
static uint32_t sec   = 0;

static void timer_phase(int hz)
{
  int divisor = 1193180 / hz;                           /* Calculate our divisor */

  uint8_t l = (divisor & 0xFF);
  uint8_t h = (divisor >> 8);
  outb(IO_CMD_PORT, IO_COMMAND);                        /* Set our command byte 0x36 */
  outb(IO_CMD_SPACE(0),      l);                        /* Set low byte of divisor */
  outb(IO_CMD_SPACE(0),      h);                        /* Set high byte of divisor */
}

void timer_handler(regs ctx)
{
  ticks++;

  if(ticks % 100 == 0) { 
    sec++;
    printk(KERN_DEBUG "Seconds: %d\n", sec); 
  }
  timer_phase(100); // 60 Hz
}

void timer_install()
{
  irq_install_handler(0, timer_handler);
}

#pragma GCC diagnostic pop

