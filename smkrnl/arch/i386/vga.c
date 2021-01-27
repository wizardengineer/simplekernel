#include "../../include/kernel/vga.h"

void vga_putchar(int i, char c, vga_colors fg, vga_colors bg)
{
  framebuffer_rw[i]     = c;
  framebuffer_rw[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}


