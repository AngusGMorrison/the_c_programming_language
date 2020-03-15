#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Write a version of itao that accepts three arguments instead of two. The
 * third argument is a minimum field width; the converted number must be padded
 * with blanks on the left if necessary to make it wide enough.
 */

#define MAX_LEN 100

void itoa(int n, char s[], int width);
void reverse(char s[]);

int main() {
    char s[MAX_LEN];
    itoa(-500, s, 5);
    printf("%s\n", s);

}

void itoa(int n, char s[], int width) {
    int sign = n;
    int i = 0;

    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    while (i < width) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    char temp;
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[j], s[j] = s[i], s[i] = temp;
    }
}