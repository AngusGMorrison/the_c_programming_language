#include <stdio.h>
#include <string.h>

/**
 * Write the function strrindex(s, t), which returns the position of the
 * rigtmost occurrence of t in s, or -1 if there is none.
 */

int strrindex(char s[], char t);

int main() {
    char test[] = "Gnarlborough";
    printf("%i\n", strrindex(test, 'o'));
}

int strrindex(char s[], char t) {
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] == t) return i;
    }
    return -1;
}