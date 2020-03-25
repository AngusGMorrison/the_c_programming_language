/**
 * Write versions of the library functions strncpy, strncat, and strncmp, which
 * operate on at most the first n characters of their argument strings. For
 * example, strncpy(s, t, n) copies at most n characters of t to s. Full
 * descriptions are in Appendix B.
 */

#include <stdio.h>

void copy_n(char *s, char *t, int n);
void cat_n(char *s, char *t, int n);
int comp_n(char *s, char *t, int n);

int main() {
    char s[] = "catdog";
    char t[] = "batmathat";
    copy_n(s, t, 9);
    printf("%s\n", s);

    char u[] = "rathog";
    char v[] = "hatlog";
    cat_n(u, v, 7);
    printf("%s\n", u);

    char x[] = "abfdef";
    char y[] = "abeefg";
    printf("%i\n", comp_n(x, y, 3));
}

void copy_n(char *s, char *t, int n) {
    char *s_end = s;
    while (*s_end)
        s_end++;

    for (int i = 0; i < n && *t; i++)
        *s++ = *t++;
        
    if (s >= s_end)
        *s = '\0';
}

void cat_n(char *s, char *t, int n) {
    while (*s)
        s++;
    
    for (int i = 0; i < n && *t; i++)
        *s++ = *t++;

    *s = '\0';
}

int comp_n(char *s, char *t, int n) {
    for( ; n > 0 && *s && *t; n--, s++, t++) {
        if (*s != *t)
            return *s - *t;
    }
    
    return 0;
}