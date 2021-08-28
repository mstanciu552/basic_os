#ifndef SCREEN_H_
#define SCREEN_H_

#define VIDEO_MEMORY 0xb8000
#define WHITE_ON_BLACK 0x0f

#define MAX_ROWS 25
#define MAX_COLS 80

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

unsigned short get_screen_offset(int, int);
void print_char(char, int, int, char);
unsigned short get_cursor();
void set_cursor(unsigned short int, unsigned short int);
void print_at(char*, int, int);
void clear_screen();
unsigned short handle_scrolling(unsigned short);

#endif
