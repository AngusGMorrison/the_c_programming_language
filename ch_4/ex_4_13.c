/**
 * Write a recursive version of the function reverse(s), which reverse the
 * string s in place.
 */

#include <stdio.h>
#include <string.h>

void reverse(char *s, int left, int right);

int main() {
    char s[] = "What a great string!";
    int right = strlen(s) - 1;
    reverse(s, 0, right);
    printf("%s\n", s);
}

void reverse(char *s, int left, int right) {
    if (left >= right) return;

    reverse(s, left + 1, right - 1);

    char temp = s[left];
    s[left] = s[right];
    s[right] = temp;
}