#include <stdio.h>

/**
 * Write a program to count blanks, tabs and newlines.
 */

int main() {
    int blanks = 0, tabs = 0, newlines = 0;

    int current_char;
    printf("Enter a string: ");
    while ((current_char = getchar()) != EOF) {
        if (current_char == ' ') {
            blanks++;
        } else if (current_char == '\t') {
            tabs ++;
        } else if (current_char == '\n') {
            newlines++;
        }
    }

    printf("Blanks: %i; Tabs: %i; Newlines: %i\n", blanks, tabs, newlines);
}