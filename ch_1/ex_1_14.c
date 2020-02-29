#include <stdio.h>

/**
 * Write a program to print a histogram of the frequencies of different
 * characters in its input.
 * 
 * This implementation allows for 256 ASCII characters only.
 */

#define MAX 256

int main() {
    char current_char;
    char frequencies[MAX] = { 0 };  // Initialize all array slots to 0.

    while ((current_char = getchar()) != EOF) {
        /* Because chars map directly to integers, we can use the char as an
           array index and store its frequency. */
        frequencies[current_char]++;
    }

    // Of all ASCII characters...
    for (int i = 0; i < MAX; i++) {
        // If the character occurred in the input, print it.
        if (frequencies[i] > 0) {
            if (i == '\n') {
                printf("\\n");
            } else if (i == ' ') {
                printf("sp");
            } else if (i == '\t') {
                printf("\\t");
            } else if (i == '\\') {
                printf("\\");
            } else {
                putchar(i);
            }
            
            putchar('\t');
            // Print hashes equal to the number of times it occurred.
            for (int j = 0; j < frequencies[i]; j++) {
                putchar('#');
            }
            putchar('\n');
        }
    }
}