#include "../headers/mem.h"

unsigned char *memory_cpy(unsigned char *dest, const unsigned char *src, int count, int step) {

  for (int i = 0; i < count; i++) dest[i*2] = src[i];
  return dest;
}

unsigned char port_byte_in(unsigned short port) {
  unsigned char result;

  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));

  return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in(unsigned short port) {
  unsigned short result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void port_word_out(unsigned short port, unsigned short data) {
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}