/**
 * Rewrite the postf ix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number conversion.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

void push(double op);
double pop();
int getop(char s[], double *d);

int main() {
    int type;
    double d, op2;
    char s[MAXOP];

    while((type = getop(s, &d)) != EOF) {
        switch (type) {
            case NUMBER:
                push(d);
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

#define MAXVAL 100
int stack_pos = 0;
double stack[MAXVAL];

// Push op onto stack
void push(double op) {
    if (stack_pos < MAXVAL) {
        stack[stack_pos++] = op;
    } else {
        printf("Error: stack full, can't push %f\n", op);
    }
}

// Pop and return top value from stack
double pop() {
    if (stack_pos > 0) {
        return stack[--stack_pos];
    } else {
        printf("Error: stack empty\n");
        return 0.0;
    }
}

// Get next operator or numeric operand
int getop(char s[], double *d) {
    char current;
    int match_count;

    while ((match_count = scanf("%c", &current)) != EOF) {
        if ((s[0] = current) != ' ' && current != '\t') {
            break;
        }
    }
    s[1] = '\0';

    if (match_count == EOF) {
        return EOF;
    } else if (!isdigit(current) && current != '.') {
        return current;
    }

    ungetc(current, stdin);
    scanf("%lf", d);
    return NUMBER;
}