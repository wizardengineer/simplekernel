#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t terminal_row = 0;
static size_t terminal_column = 0;
static uint8_t terminal_color = 0;

void terminal_initialize()
{
  terminal_color = vga_entry_color(VGA_WHITE, VGA_BLACK);
  for(size_t y = 0; y < VGA_HEIGHT; y++) {
    for(size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      FRAMEBUFFER_MEMORY[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  FRAMEBUFFER_MEMORY[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if(++terminal_column == VGA_WIDTH && ++terminal_row == VGA_HEIGHT) {
    terminal_column = 0;
    terminal_row = 0;
  }
}


