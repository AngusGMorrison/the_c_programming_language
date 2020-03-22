/**
 * As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 */

#include <ctype.h>
#include <stdio.h>

int getch();
void ungetch(int c);

// getint: get next integer from input into *pn
int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch())) 
        ;   // Skip whitespace
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        // Not a number
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        char prev = c;
        if (!isdigit(c = getch())) {
            // Not a number
            if (c != EOF) {
                ungetch(c);     // Push back non-digit
            }
            ungetch(prev);      // Push back sign char
            return 0;           // Return code for not a number
        }
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }
    return c;
}

#define BUFSIZE 5

int buffer[BUFSIZE];
int buf_pos = 0;

int getch() {
    return buffer[buf_pos] != 0 ? buffer[buf_pos] : getchar();
}

void ungetch(int c) {
    if (buf_pos < BUFSIZE - 1) {
        buffer[buf_pos++] = c;
    } else {
        printf("Buffer full\n");
    }
}
