#include <stdio.h>
#include <stdlib.h>

/**
 * Given the basic framework, it's straightforward to extend the calculator.
 * Add the modulus (%) operator and provisions for negative numbers.
 */ 

#define MAXOP 100   // Max size of operand or operator
#define NUMBER '0'  // Signal that a number was found

int getop(char []);
void push(double);
double pop(void);

// Reverse Polish calculator
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("Error: zero divisor\n");
                }       
                break;
            case '%':
                op2 = pop();
                push((double) ((int) pop() % (int) op2));
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("Error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

#define MAXVAL 100      // Maximum depth of val stack

int sp = 0;             // Next free stack position
double val[MAXVAL];     // Value stack

// push: push f onto value stack
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("Error: stack full, can't push %g\n", f);
    }
}

// pop: pop and return top value from stack
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("Error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

// getop: get the next operator or numeric operand
int getop(char s[]) {
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-') {
        return c;   // Not a number
    }

    i = 0;

    if (c == '-' && !isdigit((s[++i] = c = getch()))) {
        ungetch(c);
        return '-';
    }

    if (c == '-' || isdigit(c)) {
        // Collect integer part
        while (isdigit(s[++i] = c = getch())) 
            ;
    }
    if (c == '.') {
        // Collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';

    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  // Buffer for ungetch
int bufp = 0;       // Next free position in buf

// getch: get a possibly pushed-back character
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push character back on input
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}