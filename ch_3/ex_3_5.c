#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Write a function itob(n, s, b) that converts the integer n into a base b
 * character representation in the string s. In particular, itob(n, s, 16)
 * formats n as a hexadecimal integer in s.
 */

#define MAX_LEN 100

void itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
    int n = 255;
    char s[MAX_LEN];
    itob(n, s, 16);
    printf("%s\n", s);

    itob(n, s, 2);
    printf("%s\n", s);

}

void itob(int n, char s[], int b) {
    int sign = n;
    int i = 0;

    do {
        int mod = abs(n % b);
        s[i++] = mod >= 10 ? mod - 10 + 'A' : mod + '0';
    } while ((n /= b) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
}