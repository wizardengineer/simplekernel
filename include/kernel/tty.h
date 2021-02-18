#ifndef _KENREL_TTY_H
#define _KERNEL_TTY_H

/* simple safe guards for strings */
#define invoke_str_constraint(fmt) terminal_writeS(__func__": "fmt)

#include <kernel/printk.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_scroll();
void terminal_putchar (char c);
void terminal_write   (const char* data, size_t size);
void terminal_writeS  (const char* data);
void move_cursor ();

/* banner placement */
void _simple_banner();
void _end_banner();

#endif
