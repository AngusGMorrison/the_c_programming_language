/**
 * Write a program that will print arbitrary input in a sensible way. As a
 * minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 */

#include <ctype.h>
#include <stdio.h>

#define MAX_POS 50
#define HEX_WIDTH 8

int incr_pos(int line_pos, int char_width);
void zero_pad(char *str);

int main() {
    int current;
    int line_pos = 0;
    char buffer[9];

    while ((current = getchar()) != EOF) {
        if (current == '\n') {
            putchar('\n');
            line_pos = 0;
        } else if (!isgraph(current)) {
            line_pos = incr_pos(line_pos, HEX_WIDTH);
            sprintf(buffer, "0x%6x", current);
            zero_pad(buffer);
            printf("%s", buffer);
        } else {
            line_pos = incr_pos(line_pos, 1);
            putchar(current);
        }
    }

    return 0;
}

int incr_pos(int line_pos, int char_width) {
    line_pos += char_width;

    if (line_pos >= MAX_POS) {
        putchar('\n');
        line_pos = 0;
    }

    return line_pos;
}

void zero_pad(char *str) {
    for ( ; *str != '\0'; str++) {
        if (*str == ' ') {
            *str = '0';
        }
    }
}