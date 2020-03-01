#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * Write a program to remove trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines.
 */

#define MAX_LENGTH 1000

void trim(char line[], int length);
void print_line(char line[]);

int main() {
    char current_char;
    char current_line[MAX_LENGTH];
    int length = 0;

    while ((current_char = getchar()) != EOF) {
        // At the end of a line...
        if (current_char == '\n') {
            trim(current_line, length);
            print_line(current_line);
            length = 0;     // Reset for the next line
        } else {
            // Add the current char to the array and increment length
            current_line[length++] = current_char;
        }
    }
}

void trim(char line[], int length) {
    /* Rewind through trailing blanks until a non-blank character is
       found or the whole line has been trimmed. */
    while (isblank(line[length - 1]) && length > 0) {
        length--;
    }

    if (length > 0) {
        /* A non-blank character has been found. Follow it with a newline
        char and terminate the string. */
        line[length] = '\n';
        line[++length] = '\0';
    } else {
        line[0] = '\0'; // Discard the string
    }
}

void print_line(char line[]) {
    int length = strlen(line);
    /* To verify the string has been trimmed, make remaining blanks visible and
       confirm that empty lines don't print newline chars. */
    for (int i = 0; i < length; i++) {
        if (isblank(line[i])){
            line[i] = '#';
        } else if (line[i] == '\n') {
            line[i++] = '#';
            line[i++] = '\n';
            line[i] = '\0';
        }
    }
    if (strlen(line) > 0) {
        printf("%s\n", line);
    }
}