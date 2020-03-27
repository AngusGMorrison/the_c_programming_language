/**
 * Extend entab and detab to accept the shorthand
 *      entab -m -n
 * to mean tab stops every n columns, starting at column n. Choose convenient
 * (for the user) default behaviour.
 * 
 * Note: entab is omitted due to the difficulty of modern terminals having an
 * internal default tab size, leading to incorrect output from correct code.
 */ 

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1000
#define DEFAULT_TAB 8
#define DEFAULT_START 0

int replace_tab(char line[], int length, char *tab_stops[]);
void print(char *line);

int main(int argc, char *argv[]) {
    int tab_col = DEFAULT_TAB;
    int tab_start = DEFAULT_START;

    if (argc == 3) {
        tab_col = atoi(argv[1]);
        tab_start = atoi(argv[2]);
    }

    char current_char;
    char line[MAX_LINE];
    int length = 0;
    int spaces_req;

    while ((current_char = getchar()) != EOF && current_char != '\n') {
        if (current_char == '\t') {
            if (length >= tab_start) {
                spaces_req = tab_col - ((length - tab_start) % tab_col);
                for (int i = 0; i < spaces_req; i++)
                    line[length++] = ' ';
            } 
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