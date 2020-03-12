#include <stdio.h>

/**
 * Write  a loop equivalent to the for loop above without using && or ||.
 */

#define MAX 1000

int main() {
    int i = 0;
    int lim = MAX;
    int s[MAX];
    char c;

    while (i < lim - 1) {
        if ((c = getchar()) == '\n') {
            break;
        } else if (c == EOF) {
            break;
        }
        s[i++] = c;
    }
}