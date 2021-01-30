#include <kernel/vga.h>
#include <kernel/tty.h>
#include <io/serial_port.h>

void kmain()
{
  terminal_initialize();
  terminal_writeS("SimpleKernel");
  serial_writeS("Testing: SimpleKernel");
}
