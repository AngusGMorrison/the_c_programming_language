/**
 * Write getfloat, the floating-point analog of getint. What type does getfloat
 * return as its function value.
 * 
 * Answer: getfloat returns ints to signal execution status. The floats it
 * produces are assigned directly to the array address passed in.
 */

#include <stdio.h>

int getfloat(double *pn);

int main() {
    double arr[1];
    getfloat(&arr[0]);
    printf("%f\n", arr[0]);
}

#include <ctype.h>
#include <math.h>

int getch();
void ungetch(int c);

int getfloat(double *pn) {
    int current, sign;

    while (isspace(current = getch()))
        ;   // Skip white space

    if (!isdigit(current) && current != EOF && current != '+' && current != '-') {
        ungetch(current);   // Not a number
        return 0;
    }

    sign = (current == '-') ? -1 : 1;
    if (current == '+' || current == '-') {
        current = getch();
    }

    for (*pn = 0.0; isdigit(current); current = getch()) {
        *pn = 10.0 * *pn + (current - '0');
    }

    if (current == '.') {
        int decimal_places = 0;
        while (isdigit(current = getch())) {
            *pn = 10.0 * *pn + (current - '0');
            decimal_places++;
        }
        *pn /= pow(10, decimal_places);
    }

    *pn *= sign;

    if (current != EOF) {
        ungetch(current);
    }

    return current;
}

#define BUFSIZE 5

int buffer[BUFSIZE];
int buf_pos = 0;

int getch() {
    return buf_pos > 0 ? buffer[--buf_pos] : getchar();
}

void ungetch(int c) {
    if (buf_pos < BUFSIZE) {
        buffer[buf_pos++] = c;
    } else {
        printf("Buffer full\n");
    }
}


