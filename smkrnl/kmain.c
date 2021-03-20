#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/printk.h>
#include <kernel/gdt.h>
#include <kernel/pit_i8254.h>
#include <io/serial_port.h>
#include <stdio.h>
#include <string.h>

/* Externs of security type functions */
extern void supervisor_protection_init(); // smep and smap

void kmain()
{
  /* IRQ type functions */
  timer_install();
  keyboard_install();

  /* Security type functions*/
  supervisor_protection_init();

}
