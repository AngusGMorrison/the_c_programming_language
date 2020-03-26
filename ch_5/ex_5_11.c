/**
 * Modify the programs entab and detab (written as exercises in Chapter 1) to
 * accept a list of tab stops as arguments. Use the default tab settings if
 * there are no arguments.
 * 
 * Note: entab is omitted due to the difficulty of modern terminals having an
 * internal default tab size, leading to incorrect output from correct code.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1000
#define DEFAULT_TAB 8

int replace_tab(char line[], int length, char *tab_stops[]);
void print(char *line);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: ./ex_5_11.c 8 4 6 5...");
        return 1;
    }

    char current_char;
    char line[MAX_LINE];
    int length = 0;
    int next_stop = 0;
    int spaces_req;

    while ((current_char = getchar()) != EOF && current_char != '\n') {
        if (current_char == '\t') {
            while (length >= next_stop && *++argv)
                next_stop += atoi(*argv);

            spaces_req = next_stop - length > 0 ? next_stop - length : 0;
            for (int i = 0; i < spaces_req; i++)
                line[length++] = ' ';
        } else {
            line[length++] = current_char;
        }
    }

    if (current_char == '\n') {
        line[length++] = '\n';
    }

    line[length] = '\0';
    print(line);
}

void print(char *line) {
    while (*line) {
        if (*line == ' ')
            putchar('.');
        else
            putchar(*line);
        line++; 
    }
    putchar('\n');
}