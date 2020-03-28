/**
 * Write the progam tail, which prints the last n lines of its input. By
 * default, n is 10, let us say, but it can be changed by an optional argument,
 * so that
 *      tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program of Section 5.6, not in a two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>

#define DEF_PRINT_LINES 10
#define MAX_LINES 1000

int read_lines(char *lines[], int max_lines);
int get_line(char *line, int lim);

int main(int argc, char *argv[]) {
    int lines_to_print = DEF_PRINT_LINES;
    if (argc == 2)
        lines_to_print = atoi(argv[1]);

    char *lines[MAX_LINES];
    int nlines;

    if ((nlines = read_lines(lines, MAX_LINES)) > 0) {
        int print_loc = nlines - lines_to_print;
        if (print_loc < 0)
            print_loc = 0;

        while (print_loc < nlines)
            printf("%s\n", lines[print_loc++]);
    }

    return 0;
}

#include<string.h>

#define MAX_LEN 1000

int read_lines (char *lines[], int max_lines) {
    int len, nlines;
    char *p, line[MAX_LEN];

    nlines = 0;
    while ((len = get_line(line, MAX_LEN)) > 0) {
        if (nlines >= max_lines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';   // Delete newline
            strcpy(p, line);
            lines[nlines++] = p;
        }
    }
    return nlines;
}

int get_line(char *line, int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        *line++ = c;
    
    if (c == '\n') {
        *line++ = '\n';
        i++;
    }

    *line = '\0';
    return i;
}