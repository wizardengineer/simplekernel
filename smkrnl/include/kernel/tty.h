#ifndef _KENREL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar (char c);
void terminal_write   (const char* data, size_t size);
void terminal_writeS  (const char* data);

#endif
