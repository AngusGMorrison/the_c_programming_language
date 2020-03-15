#include <stdio.h>

/**
 * Write a function expand(s1, s2) that expands shorthand notations like a]-z in
 * the string s1 into the equivalent complete list abc...xyz in s2. Allow for
 * letters of either case and digits, and be prepared to handle cases like a-b-c
 * and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
 */

#define MAX_LEN 1000

void expand(char s1[], char s2[]);

int main() {
    char s1[] = "a-za-b-z0-9";
    char s2[MAX_LEN];
    expand(s1, s2);
    printf("%s\n", s2);
}

void expand(char s1[], char s2[]) {
    int i, j, current;
    i = j = 0;

    while ((current = s1[i++]) != '\0') {
        if (s1[i] == '-' && s1[i + 1] >= current) {
            i++;
            while (current < s1[i]) {
                s2[j++] = current++;
            }
        } else {
            s2[j++] = current;
        }
    }
    s2[j] = '\0';
}