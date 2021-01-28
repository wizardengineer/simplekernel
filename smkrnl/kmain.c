#include <kernel/vga.h>
#include <kernel/tty.h>

void kmain()
{
  terminal_initialize();

  terminal_putchar('S');
}
