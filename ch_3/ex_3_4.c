#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * In a two's complement number representation, our version of itoa does not
 * include the largest negative number, that is, the value of n equal to
 * -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 * 
 * Explanation: At n = -n, the largest negative integer, -2,147,483,648, can't
 * be made positive without overflowing. The maximum possible value of a
 * positive signed integer is 2,147,483,647.
 */

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
    char s[100];
    itoa(-2147483648, s);
    printf("%s\n", s);
}

void itoa(int n, char s[]) {
    int sign = n;
    int i = 0;

    do {
        /* Taking the absolute value of n % 10 means n isn't converted to a
           positive number until it is less than the maximum negative value. */
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) < 0);

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