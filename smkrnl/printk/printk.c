#define pr_fmt(fmt) "%s: " fmt, __func__

#if defined(__KERNEL_MOD)
  #include <kernel/tty.h>
  #include <kernel/vga.h>
  #include <kernel/kern_levels.h>
  #include <kernel/printk.h>
#endif

#include <stdio.h>
#include <string.h>

/* simple printk will be adding more features soon*/

void printk(const char* restrict format, ...)
{
#if defined(__KERNEL_MOD)
  va_list parameters;
  va_start(parameters, format);
  __vsprintf_w(NULL, terminal_putchar, format, parameters);
  va_end(parameters);
#else
  /* TODO: Implement a way to make sure this isn't being used in usrmode*/
#endif
}




