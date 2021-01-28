#include <kernel/vga.h>

void kmain()
{
  vga_putchar(0, 'S', VGA_WHITE, VGA_BLACK);
}
