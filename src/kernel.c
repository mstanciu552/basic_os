#include "../headers/mem.h"
#include "../headers/screen.h"

void print_ch(const char *);

typedef struct char_with_attribute {
    char ch, attribute;
} char_with_attribute;

char_with_attribute* convert_to_struct(char, char);

void main(void) {
    volatile char_with_attribute *video_memory = (void*)VIDEO_MEMORY;
    const char* str = "Hello World!";

    clear_screen();
    print_ch(str);
}

char_with_attribute* convert_to_struct(char ch, char attr) {
    char_with_attribute* combination;

    combination->ch = ch;
    combination->attribute = attr;

    return combination;
}

void print_ch(const char* str) {
    char* vidmem = (void*) VIDEO_MEMORY;
    while (*str) {
        *vidmem++ = *str++;
        *vidmem++ = 0x0f;
    }
}
