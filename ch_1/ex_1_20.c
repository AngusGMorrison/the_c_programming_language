#include <stdio.h>

/**
 * Write a program detab that replaces tabs in the input with the proper number
 * of blanks to space to the next tab stop. Assume a fixed set of tab stops, say
 * every n columns. Should n be a variable or a symbolic parameter?
 */

#define MAX_LINE 1000
/* Tab stops should not be editable within the program itself, so a symbolic
   constant is desirable. */
#define TAB_SPACES 4

int replace_tab(char line[], int length);

int main() {
    char current_char;
    char line[MAX_LINE];
    int length = 0;

    while ((current_char = getchar()) != EOF && current_char != '\n') {
        if (current_char == '\t') {
            length = replace_tab(line, length);
        } else {
            line[length++] = current_char;
        }
    }

    if (current_char == '\n') {
        line[length++] = '\n';
    }

    line[length] = '\0';
    printf("%s\n", line);
}

int replace_tab(char line[], int length) {
    // Calculate how many spaces are required to reach the next tab stop
    int spaces = TAB_SPACES - (length % TAB_SPACES);
    for (int i = 0; i < spaces; i++) {
        line[length++] = ' ';
    }
    return length;
}