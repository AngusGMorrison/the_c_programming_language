#include <stdio.h>

/**
 * Write a program to count blanks, tabs and newlines.
 */

int main() {
    int blanks = 0, tabs = 0, newlines = 0;

    int c;
    printf("Enter a string: ");
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blanks++;
        } else if (c == '\t') {
            tabs ++;
        } else if (c == '\n') {
            newlines++;
        }
    }

    printf("Blanks: %i; Tabs: %i; Newlines: %i\n", blanks, tabs, newlines);
}