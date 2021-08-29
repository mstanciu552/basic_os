#ifndef MEM_H_
#define MEM_H_

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

unsigned char *memory_cpy(unsigned char*, const unsigned char*, int, int);
unsigned char port_byte_in(unsigned short);
void port_byte_out(unsigned short, unsigned char);
unsigned short port_word_in(unsigned short);
void port_word_out(unsigned short, unsigned short);

#endif
