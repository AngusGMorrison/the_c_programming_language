#include <stdio.h>
#include <ctype.h>

/**
 * Write an alternate version of squeeze(s1, s2) that deletes each character
 * in s1 that matches any character in s2.
 */

void squeeze(char s1[], char s2[]);

int main() {
    char s1[] = "Hello cat. Bye bye bat. Brackets are crap.";
    char s2[] = "abc";
    squeeze(s1, s2);
    printf("%s\n", s1);
}

void squeeze(char s1[], char s2[]) {
    int offset = 0;
    for (int i = 0; s1[i - offset] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (tolower(s1[i - offset]) == tolower(s2[j])) {
                for (int k = i - offset; s1[k] != '\0'; k++) {
                    s1[k] = s1[k + 1];
                }
                offset++;
                break;
            }
        }
    }
}