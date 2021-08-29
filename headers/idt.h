
#include "mem.h"

typedef struct {
  uint16_t low_offset;
  uint16_t selector;
  uint8_t always0;
  uint8_t flags;
  uint16_t high_offset;
} idt_gate_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} idt_register_t;

void set_idt_gate(int n, uint32_t handler);
void load_idt();
