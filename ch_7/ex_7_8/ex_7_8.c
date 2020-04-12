/**
 * Write a program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 60
#define LINES_ON_PAGE 50

void print_file(FILE *file, char *filename);
int print_heading(char *filename);

int main(int argc, char *argv[]) {
    FILE *file;

    if (argc == 1) {
        fprintf(stderr, "Usage: ./ex_7_8 <file 1> [<file 2> <file 3> ...]\n");
        exit(1);
    }

    while (--argc > 0) {
        if ((file = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "Error: unable to open file %s\n", *argv);
            exit(2);
        }
        print_file(file, *argv);
        fclose(file);
    }

    exit(0);
}

void print_file(FILE *file, char *filename) {
    int line_count = 0;
    char line[LINE_LEN];
    int pages = 1;
    
    line_count = print_heading(filename);

    while (fgets(line, LINE_LEN, file) != NULL) {
        if (line_count == LINES_ON_PAGE - 2) {;
            printf("\nPage %i\f", pages);
            line_count = 0;
            pages++;
        }

        printf("%s", line);
        line_count++;
    }

    printf("\nPage %i\n\f", pages);
}

int print_heading(char *filename) {
    printf("%s\n\n\n", filename);
    int lines = 3;
    return lines;
}