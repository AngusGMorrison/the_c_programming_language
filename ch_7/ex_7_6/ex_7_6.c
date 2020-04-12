/**
 * Write a program to compare two files, printing the first line where they
 * differ.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

int get_line(char *line, int max, FILE* file);

int main(int argc, char *argv[]) {
    FILE *f1, *f2;
    char line1[MAX_LINE], line2[MAX_LINE];
    int len1, len2;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: ./ex_7_6 <file 1> <file 2>\n");
        exit(1);
    }

    if ((f1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: failed to open file %s\n", argv[1]);
        exit(2);
    }
    
    if ((f2 = fopen(argv[2], "r")) == NULL) {
        fclose(f1);
        fprintf(stderr, "Error: failed to open file %s\n", argv[2]);
        exit(2);
    }

    while ((len1 = get_line(line1, MAX_LINE, f1)) && (len2 = get_line(line2, MAX_LINE, f2))) {
        if (strcmp(line1, line2) != 0) {
            printf("File 1: %s\n", line1);
            printf("File 2: %s\n", line2);
            break;
        }
    }

    if (len1 - len2 != 0) {
        printf("File 1: %s\n", len1 > len2 ? line1 : "");
        printf("File 2: %s\n", len2 > len1 ? line2 : "");
    }

    fclose(f1);
    fclose(f2);
    exit(0);
}

int get_line(char *line, int max, FILE* file) {
    if (fgets(line, max, file) == NULL) {
        return 0;
    } else {
        return strlen(line);
    }
}