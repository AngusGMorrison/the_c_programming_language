/**
 * Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s, t) copies the string t to the end of s.
 */

#include <stdio.h>

void str_cat(char *s, char *t);

int main() {
    char s[] = "Hello, ";
    char t[] = "World.";
    str_cat(s, t);
    printf("%s\n", s);
}

void str_cat(char *s, char *t) {
    while (*s)
        s++;
    while ((*s++ = *t++))
        ;
} 