#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * An alternative organization uses getline to read an entire input line; this
 * makes getch and ungetch unnecessary. Revise the calculator to use this
 * approach.
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
#include <string.h>

#define MAX_LINE 100

int get_line(void);

char line[MAX_LINE];
int idx = 0;

// getop: get the next operator or numeric operand
int getop(char s[]) {
    // Get a new line if the current line is empty or the index is at the end
    if (line[idx] == '\0') {
        if (get_line() == 0) {
            return EOF;
        } else {
            idx = 0;
        }
    }

    int current_char;

    // Skip blanks
    while((s[0] = current_char = line[idx++]) == ' ' || current_char == '\t')
        ;

    if (!isdigit(current_char) && current_char != '.' && current_char != '-') {
        return current_char;
    }

    if (current_char == '-' && !isdigit(line[idx])) {
        return '-';
    }

    int i = 1;

    if (current_char == '-' || isdigit(current_char)) {
        // Collect integer part
        while (isdigit(s[i++] = current_char = line[idx++])) 
            ;
    }

    if (current_char == '.') {
        // Collect fraction part
        while (isdigit(s[i++] = current_char = line[idx++]))
            ;
    }
    
    s[i] = '\0';

    return NUMBER;
}

int get_line(void) {
    int i, current_char;

    for (i = 0;
         i < MAX_LINE - 1 &&
         (current_char = getchar()) != EOF &&
         current_char != '\n';
         i++) {
             line[i] = current_char;
    }

    if (current_char == '\n') {
        line[i++] = '\n';
    }

    line[i] = '\0';
    return i;
}