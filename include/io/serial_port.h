#ifndef _SERIAL_PORT
#define _SERIAL_PORT
#include <kernel/kern_levels.h>

int serial_received();

// Reading the received data
//
char read_serial();

int is_transmit_empty();

void write_serial(char a);

void serial_print(const char* buffer, ...);

#endif
