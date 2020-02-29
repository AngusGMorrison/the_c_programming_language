#include <stdio.h>

/**
 * Write a program to print all input lines longer than 80 characters.
 */

#define MAX_LENGTH 1000
#define THRESHOLD 80

int main() {
    char current_line[MAX_LENGTH];
    int length = 0;
    char current_char;

    while ((current_char = getchar()) != EOF) {
        current_line[length] = current_char;
        length++;
        /* If the line ends, print it if its length exceeds the threshold. Once
           printed, or if it is too short to be printed, reset the length
           counter. */
        if (current_char == '\n') {
            if (length > THRESHOLD) {
                current_line[length] = '\0';
                printf("%s\n", current_line);
            }
            length = 0;
        }
    }
}