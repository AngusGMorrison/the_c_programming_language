#include <stdio.h>

/**
 * Verify that the expression getchar() != EOF is 0 or 1.
 */

int main() {
    // Prints out the value of c != EOF. When EOF is entered, the loop breaks.
    // Enter EOF with ctrl+D on Linux/OSX, or ctrl+Z on Windows.
    while (1) {
        printf("Enter a charater to test: ");
        int c = getchar();
        // The second getchar exists only to absorb the newline char at the end
        // of user input
        getchar();
        printf("c != EOF: %i\n", c != EOF);
        if (c == EOF) break;
    }
}