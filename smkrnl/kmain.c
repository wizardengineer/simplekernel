#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/printk.h>
#include <io/serial_port.h>
#include <stdio.h>
#include <string.h>
#include <kernel/gdt.h>

void kmain()
{
  printk("Kernel main is running\n");
}
