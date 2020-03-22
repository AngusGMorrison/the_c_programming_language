/**
 * Write the function strend(s, t), which returns 1 if the string t occurs at the
 * end of the string s, and zero otherwise.
 */

#include <stdio.h>

int strend(char *s, char *t);

int main() {
    char s[] = "concat";
    char t[] = "cat";
    printf("%i\n", strend(s, t));
}

int strend(char *s, char *t) {
    char *s_start = s;
    char *t_start = t;

    while (*s)
        s++;
    while (*t)
        t++;
    
    if ((t - t_start) > (s - s_start))
        return 0;

    while (t > t_start)
        if (*--t != *--s)
            return 0;

    return 1;
}