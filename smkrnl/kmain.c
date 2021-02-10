#include <kernel/vga.h>
#include <kernel/tty.h>
#include <io/serial_port.h>
#include <stdio.h>
#include <string.h>
#include <kernel/gdt.h>

void kmain()
{
  terminal_initialize();
  printf("\t\t\t\t\t\t\t\t" "SimpleKernel\n");
  serial_writeS("Testing: SimpleKernel");
}
