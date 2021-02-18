#ifndef IO_H
#define IO_H

// the I/O ports
#define COMMAND_PORT         0x3D4
#define DATA_PORT            0x3D5

//  the I/O port commands 
#define HIGH_BYTE_COMMAND   0x0E 
#define LOW_BYTE_COMMAND    0x0F

#include <stdint.h>

/*
 *  @outb   -> Sends the given data to the given I/O port. Defined in io.s
 *  @param  -> port -> The I/O port to send the data to
 *  @param  -> data -> The data to send to the I/O port
 */

void outb(uint16_t port, uint8_t data);

/* inb:
 *  Read a byte from an I/O port.
 *
 *  @param  port The address of the I/O port
 *  @return      The read byte
 */

uint8_t inb(uint16_t port);

#endif
