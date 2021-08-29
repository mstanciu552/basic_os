#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "mem.h"

typedef struct {
  uint16_t low_offset;
  uint16_t selector;
  uint8_t always0;
  uint8_t flags;
  uint16_t high_offset;
} __atribute__((packed)) idt_gate_t;

#endif
