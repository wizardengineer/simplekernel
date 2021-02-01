#include <kernel/tty.h>
#include <kernel/vga.h>
#include <io/io_port.h>
#include <stdint.h>
#include <string.h>

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

void terminal_scroll(){
  for(size_t y=0; y<VGA_HEIGHT; ++y){
    for(size_t x=0; x<VGA_WIDTH; ++x){
      const size_t source = y * VGA_WIDTH + x;
	if(y){
	  const size_t dest = (y-1) * VGA_WIDTH + x;
	  FRAMEBUFFER_MEMORY[dest]=FRAMEBUFFER_MEMORY[source];
	}
	  terminal_putentryat(' ', terminal_color, x, y);
	}
    }
  terminal_column=0;
  terminal_row=VGA_HEIGHT-1;
  move_cursor((terminal_row * 80) + terminal_column);
}

void terminal_putchar(char c)
{
  if(c == '\n'){
  if(++terminal_row >= VGA_HEIGHT){
    terminal_scroll();
  }
  terminal_column = 0;
  return;
  } else if(c == '\t'){
    c=' ';
  }

  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

  if(++terminal_column == VGA_WIDTH) 
  {
    terminal_column = 0;
    if(++terminal_row == VGA_HEIGHT) 
    {
      terminal_scroll();
      terminal_row = 0;
    }
  }
}

void terminal_write(const char* data, size_t size)
{
  for(unsigned int i = 0; i < size; i++) { terminal_putchar(data[i]); }
  move_cursor((terminal_row * 80) + terminal_column);
}

void terminal_writeS(const char* string)
{
  terminal_write(string, strlen(string));
}

void move_cursor(uint16_t pos)
{
  // low port
  outb(COMMAND_PORT, LOW_BYTE_COMMAND);
  outb(DATA_PORT,    pos & 0x00FF);

  // high port
  outb(COMMAND_PORT, HIGH_BYTE_COMMAND);
  outb(DATA_PORT,    ((pos >> 8) & 0x00FF));
 }
