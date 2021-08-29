#include "../headers/mem.h"
#include "../headers/screen.h"

int main(void) {
    char* str = "Hello, World!";

    clear_screen();
    print_at(str, 0, 0);
    return 0;
}
