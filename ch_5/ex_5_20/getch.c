/**
 * getch and ungetch methods providing character pushback functionality.
 */

#include <stdio.h>

#define MAXBUF 10

static int buf[MAXBUF];
static int bufpos = 0;

// Return a character from the stack if there is one, else getchar
int getch(void) {
    return bufpos > 0 ? buf[--bufpos] : getchar();
}

void ungetch(int c) {
    if (bufpos < MAXBUF - 1) {
        buf[bufpos++] = c;
    } else {
        printf("Error: buffer full. '%c' overflowed.\n", c);
    }
}