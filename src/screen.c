#include "../headers/screen.h"

unsigned short get_screen_offset(int cols, int rows) {
  return 2 * (rows * MAX_COLS + cols);
}

void print_char(char character, int col, int row, char attribute_byte) {
  unsigned char* vidmem = (unsigned char*) VIDEO_MEMORY;

  if (!attribute_byte) {
    attribute_byte = WHITE_ON_BLACK;
  }

  unsigned short offset;

  if (col >= 0 && row >= 0) offset = get_screen_offset(col, row);
  else offset = get_cursor();

  if (character == '\n') {
    int rows = offset / (2 * MAX_COLS);
    offset = get_screen_offset(MAX_COLS - 1, rows);
  } else {
    vidmem[offset] = character;
    vidmem[offset + 1] = attribute_byte;
  }

  offset += 2;

  offset = handle_scrolling(offset);

  set_cursor(0, offset);
}

unsigned short get_cursor () {
  port_byte_out(REG_SCREEN_CTRL, 14);
  unsigned short offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);

  return offset;
}

void set_cursor(unsigned short int x, unsigned short int y) {
  unsigned short temp = x * MAX_COLS + y;
  port_byte_in(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, temp >> 8);
  port_byte_in(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, temp);
}

void print_at(char* message, int cols, int rows) {
  if (rows >= 0 && cols >= 0)
    set_cursor(cols, rows);

  int i = 0;
  while (message[i] != 0) {
    print_char(message[i++], cols++, rows, WHITE_ON_BLACK);
    if (cols > MAX_COLS) {
      rows ++;
      cols = 0;
    }
  }
}

void clear_screen() {
  char* vidmem = (char*) VIDEO_MEMORY;
  unsigned int i = 0;
  while (i < (2 * MAX_ROWS * MAX_COLS)) {
    vidmem[i++] = ' ';
    vidmem[i++] = (char) WHITE_ON_BLACK;
  }
  set_cursor(0, 0);
}

unsigned short handle_scrolling(unsigned short offset) {
  if (offset < MAX_ROWS * MAX_COLS * 2) return offset;

  for (int i = 0; i < MAX_ROWS; i++)
    memory_cpy(get_screen_offset(0, i) + VIDEO_MEMORY, get_screen_offset(0, i - 1) + VIDEO_MEMORY, MAX_COLS * 2, 1);

  char* last_line = (char*) get_screen_offset(0, MAX_ROWS - 1) + VIDEO_MEMORY;
  for (int i = 0; i < 2 * MAX_COLS; i++)
    last_line[i] = 0;
  
  offset -= 2 * MAX_COLS;

  return offset;
}
