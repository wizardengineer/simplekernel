#ifndef _KENREL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

void terminal_initialize(void);
void terminal_scroll();
void terminal_putchar (char c);
void terminal_write   (const char* data, size_t size);
void terminal_writeS  (const char* data);
void move_cursor ();

#endif
