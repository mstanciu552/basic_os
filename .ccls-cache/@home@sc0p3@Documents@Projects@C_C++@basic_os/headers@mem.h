#ifndef MEM_H_
#define MEM_H_

#include <stdint.h>

#define low_16(addr) (uint16_t)((addr) & 0xFFFF)
#define high_16(addr) (uint16_t)((addr >> 16) & 0xFFFF)

unsigned char *memory_cpy(unsigned char*, const unsigned char*, int, int);
unsigned char port_byte_in(unsigned short);
void port_byte_out(unsigned short, unsigned char);
unsigned short port_word_in(unsigned short);
void port_word_out(unsigned short, unsigned short);

#endif
