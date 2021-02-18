#include <kernel/tty.h>
#include <kernel/vga.h>
#include <io/io_port.h>
#include <stdint.h>
#include <string.h>

// Make a pixel(2 bytes), background is always black, a is a char, b is foreground color
#define PAINT(a,b) (((b & 0xF) << 8) | (a & 0xFF))

// Get pixel
#define PIXEL(x, y) FRAMEBUFFER_MEMORY[y * 80 + x]


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t terminal_row = 0;    // x
static size_t terminal_column = 0; // y
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

void terminal_writeS(const char* data)
{
  while(*data != '\0') { terminal_putchar(*data); data++; }
}

void terminal_putchar(char c) 
{
  terminal_scroll();
  if(c == '\n') {
    terminal_row = 0;
    terminal_column++;
  }
  else if(c == '\t') {
      int i;
      for(i = 0; i < 4; i++)
        terminal_putchar(' ');
  }
  else if(c >= ' ') {
      PIXEL(terminal_row, terminal_column) = PAINT(c, terminal_color);
      terminal_row++;
      if(terminal_row == 80) {
        terminal_row = 0;
        terminal_column++;
      }
  }
    move_cursor();
}

void terminal_scroll() {
    // Move up
    void * start = (void*)FRAMEBUFFER_MEMORY + 1 * VGA_WIDTH * 2;
    uint32_t size = terminal_column * VGA_WIDTH * 2;
    if(terminal_column < 25) { return; }
    memcpy(FRAMEBUFFER_MEMORY, start, size);

    // Delete
    start = (void*)FRAMEBUFFER_MEMORY + size;
    memset(start, PAINT(0x20, terminal_color), VGA_WIDTH);
    terminal_column--;
}

void _simple_banner()
{
  terminal_setcolor(vga_entry_color(VGA_L_RED, VGA_WHITE));
  printk("\t\t\t\t\t\t\t\tSIMPLEKERNEL\n\n");
  terminal_setcolor(vga_entry_color(VGA_L_GRAY, VGA_WHITE));
  printk("============================== kernel inits ==============================\n");

}

void _end_banner()
{
  printk("==========================================================================\n");
}

void move_cursor() 
{
  unsigned curr_pos = terminal_column * VGA_WIDTH + terminal_row;
  outb(0x3D4, 14);
  outb(0x3D5, curr_pos >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, curr_pos);
}




