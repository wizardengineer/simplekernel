#include <kernel/vga.h>
#include <kernel/tty.h>
#include <io/serial_port.h>

void kmain()
{
  terminal_initialize();
  terminal_write("SimpleKernel\n", 13);
  terminal_write("SimpleKernel\n", 13);
  terminal_write("SimpleKernel\n", 13);
terminal_write("SimpleKernel\n", 13);
terminal_write("Simple kernel\n", 14);
terminal_write("SimpleKernel\n", 13);
terminal_write("SimpleKernel\n", 13);
terminal_write("SimpleKernel\n", 13);

  serial_writeS("Testing: SimpleKernel");
}
