#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Add commands for hanling variables. (It's easy to provide twenty-six
 * variables with single-letter names.) Add a variable for the most recently
 * printed value.
 */ 

#define MAXOP 100   // Max size of operand or operator
#define NUMBER '0'  // Signal that a number was found

int getop(char []);
void push(double);
double pop(void);
void peek(void);
void swap(void);
void dup(void);
void clear(void);

double last_printed = 0.0;

// Reverse Polish calculator
int main() {
    int type;
    double op2;
    char s[MAXOP];
    double variables[26] = { 0.0 };
    char last_var;

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
                break;
            case '=':
                /* = tells us this is an assignment, not a use of the variable,
                   so pop the value of the variable that was just pushed onto
                   the stack the previous operation. */
                pop();
                if (last_var >= 'A' && last_var <= 'Z') {
                    variables[last_var] = pop();
                } else {
                    printf("Invalid variable name\n");
                }
                break;
            case 's':
                swap();
                break;
            case 'v':
                dup();
                break;
            case 'c':
                clear();
                break;
            case 't':
                push(sin(pop()));
                break;
            case 'x':
                push(exp(pop()));
                break;
            case 'w':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 'p':
                peek();
                break;
            case 'l':
                printf("\t%.8g\n", last_printed);
                break;
            case '\n':
                last_printed = pop();
                printf("\t%.8g\n", last_printed);
                break;
            default:
                if (type >= 'A' && type <= 'Z') {
                    push(variables[type]);
                } else {
                    printf("Error: unknown command %s\n", s);
                }
        }
        /* Capture the most recent type to be referred back to shoudld an =
           operator be given. */
        last_var = type;
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

void peek(void) {
    if (sp > 0) {
        printf("\t%.8g\n", val[sp - 1]);
    } else {
        printf("Stack empty\n");
    }
}

void clear(void) {
    sp = 0;
}

void swap(void) {
    if (sp > 1) {
        double temp;
        temp = val[sp - 1], val[sp - 1] = val[sp - 2], val[sp - 2] = temp;
    } else {
        printf("Not enough elements to swap\n");
    }
}

void dup(void) {
    if (sp <= 0) {
        printf("No elements to dup\n");
    } else if (sp >= MAXVAL) {
        printf("Error: stack full\n");
    } else {
        val[sp] = val[sp - 1];
        sp++;
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