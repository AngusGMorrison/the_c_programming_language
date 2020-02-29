#include <stdio.h>

/**
 * Verify that the expression getchar() != EOF is 0 or 1.
 */

int main() {
    // Prints out the value of c != EOF. When EOF is entered, the loop breaks.
    // Enter EOF with ctrl+D on Linux/OSX, or ctrl+Z on Windows.
    while (1) {
        printf("Enter a character to test: ");
        int current_char = getchar();
        // The second getchar exists only to absorb the newline char at the end
        // of user input
        getchar();
        printf("current_char != EOF: %i\n", current_char != EOF);
        if (current_char == EOF) break;
    }
}