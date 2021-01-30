#ifndef _SERIAL_PORT
#define _SERIAL_PORT

int serial_received();

// Reading the received data
//
char read_serial();

int is_transmit_empty();

void write_serial(char a);

void serial_writeS(const char* buffer);

#endif
