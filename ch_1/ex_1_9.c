#include <stdio.h>

/**
 * Write a program to copy its input to its output, replacing each string of
 * one or more blanks by a single blank.
 */ 

int main() {
    int current_char, prev_char;

    printf("Enter a string: ");
    /* For each character, if the one before it wasn't a space, print it.
       This results in the first space after each non-space character being
       printed, but no more. */
    while ((current_char = getchar()) != EOF) {
        if (current_char == ' ') {
            if (prev_char != ' ') {
                putchar(current_char);
            }
        } else {
            putchar(current_char);
        }
        prev_char = current_char;
    }
}