/**
 * Modify the pattern finding program of Chapter 5 to take its input from a set
 * of named files or, if no files are named as arguments, from the standard
 * input. Should the file name be printed when a matching line is found?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_in_file(char *pattern, FILE *file, char *filename);

int main(int argc, char *argv[]) {
    char *pattern, *filename;
    int found;
    FILE *file;

    if (argc < 2) {
        fprintf(stderr, "Usage: ./ex_7_7 <pattern> [<file 1>, <file 2>, ...]\n");
        exit(-1);
    }

    pattern = *++argv;
    if (argc == 2) {
        found += find_in_file(pattern, stdin, "stdin");
    }

    found = 0;
    while (--argc > 1) {
        filename = *++argv;
        if ((file = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "Error: couldn't open file %s\n", filename);
            exit(-2);
        }

        found += find_in_file(pattern, file, filename);
        fclose(file);
    }

    return found;
}

#define MAX_LINE 1000

int find_in_file(char *pattern, FILE *file, char *filename) {
    char line[MAX_LINE];
    int found = 0;
    int line_num = 1;

    while (fgets(line, MAX_LINE, file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s, line %i: %s", filename, line_num, line);
            found++;
        }
        
        line_num++;
    }

    return found;
}