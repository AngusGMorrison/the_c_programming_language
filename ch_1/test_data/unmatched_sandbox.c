#include <stdio.h>

/**
 * This file can be used to insert unmatched brackets, and invalid escapes that
 * should be picked up by ex_1_24.
 */



int main() {
    int current_char;

    while ((current_char = getchar()) != EOF) {
        if (current_char == '\t') {
            printf("\\t");  
        } else if (current_char == '\b') {
            printf("\\b");
        } else if (current_char == '\\') {
            printf("\\");
        } else {
            putchar(current_char);
        }
    }
}