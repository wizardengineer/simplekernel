#include <kernel/vga.h>
#include <kernel/tty.h>
#include <io/serial_port.h>
#include <stdio.h>
//#include "testing.h"
#include <string.h>

void kmain()
{
  terminal_initialize();
  //video_init();
  //terminal_write("SimpleKernel", 12);
  //terminal_putchar('A');
  //terminal_putchar('A');
  //terminal_putchar('A');
  //terminal_putchar('A');
  char i = 'A';
  printf("testing baby %c \n", i);
  terminal_writeS("SimpleKernel");
  //print_string("hello\n");
  //print_string("hello\n");
  //print_string("hello");
  serial_writeS("Testing: SimpleKernel");
}
