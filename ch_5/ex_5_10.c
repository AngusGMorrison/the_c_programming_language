/**
 * Write the program expr, which evaluates a reverse Polish expression from the
 * command line, where each operator or operand is a separate argument. For
 * example, 
 *      expr 2 3 4 + *
 * evaluates 2 x (3 + 4).
 * 
 * Note: 'x' must be used instead of *, as originally suggested, becuase modern
 * terminals interpret * as a wildcard, and will tryto include the names of all
 * files in the directory as command line arguments.
 */

#include <stdio.h>

#define NUMBER 0

char getop(char *arg);
void push(double num);
double pop();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: ./ex_5_10 <reverse Polish expression>\n");
        return 1;
    }

    char current;
    double op2;
    while (--argc) {
        current = getop(*++argv);
        switch (current) {
            case NUMBER:
                break;
            case '+':
                push(pop() + pop());
                break;
            case 'x':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 > 0) {
                    push(pop() / op2);
                } else {
                    printf("Error: zero divisor\n");
                    push(0.0);
                }
                break;
            default:
                printf("Unknown command: %c\n", current);
        }
    }

    printf("%.8g\n", pop());
    return 0;
}

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char getop(char *arg) {
    if (!isdigit(arg[0]) && strlen(arg) == 1)
        return arg[0];   
    push(atof(arg));
    return NUMBER;
}

#define MAX_DEPTH 100
static double stack[MAX_DEPTH];
static int depth = 0;

void push(double num) {
    if (depth >= MAX_DEPTH) {
        printf("Error: stack depth exceeded\n");
        return;
    }
    stack[depth++] = num;
}

double pop() {
    if (depth <= 0) {
        printf("Error: stack is empty\n");
        return 0.0;
    }
    return stack[--depth];
}