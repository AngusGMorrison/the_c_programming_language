#include <stdio.h>

/**
 * Rewrite the function lower, which converts upper case letters to lower
 * case, with a conditional expression instead of if-else.
 */

char lower(char letter);

int main() {
    printf("%c\n", lower('C'));
}

char lower(char letter) {
    return (letter >= 65 && letter <= 90) ? letter - ('A' - 'a') : letter; 
}
