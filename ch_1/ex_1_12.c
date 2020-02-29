# include <stdio.h>
# include <ctype.h>

/**
 * Write a program that prints its input one word per line.
 */

int main() {
    // Initialize prev char to any non-alphanum value for the first iteration
    int current_char, prev_char = ' ';
    while ((current_char = getchar()) != EOF) {
        if (isblank(current_char)) {
            if (isalnum(prev_char)) {
                putchar('\n');
            }
        } else {
            putchar(current_char);
        }
        prev_char = current_char;
    }
}