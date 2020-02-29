#include <stdio.h>

/**
 * Write a program to copy its input to its output, replacing each tab by \t,
 * each backspace by \b, and each backslash by \\. This makes tabs and
 * backspaces visible in an unambiguous way.
 */

int main() {
    int current_char;

    while ((current_char = getchar()) != EOF) {
        if (current_char == '\t') {
            printf("\\t");  
        } else if (current_char == '\b') {
        /* Because the input stream is handled by your interactive terminal
           driver, C only sees the input once all backspaces have been
           processed and removed. If you can't see "\b" in your output, don't
           worry - this code is correct! */
            printf("\\b");
        } else if (current_char == '\\') {
            printf("\\");
        } else {
            putchar(current_char);
        }
    }
}