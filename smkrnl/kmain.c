#include <kernel/vga.h>
#include <kernel/tty.h>
#include <io/serial_port.h>
#include <stdio.h>
#include <string.h>

void kmain()
{
  terminal_initialize();
  
  printf("\t\t\t\t\t\t\t\t" "SimpleKernel\n");
  terminal_writeS("SimpleKernel");
  serial_writeS("Testing: SimpleKernel");
}
