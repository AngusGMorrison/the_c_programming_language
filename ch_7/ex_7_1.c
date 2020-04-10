/**
 * Write a program that converts upper case to lower or lower case to upper,
 * depending on the name it is invoked with, as found in argv[0].
 * 
 * 
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int current;

    int is_lower = (strcmp(argv[0], "./lower") == 0);
    int is_upper = (strcmp(argv[0], "./upper") == 0);

    if (!(is_lower || is_upper)) {
        printf("Program must be invoked as './upper' or './lower'\n");
        return 1;
    }

    if (is_lower) {
        while ((current = getchar()) != EOF) {
            putchar(tolower(current));
        }
    } else {
        while ((current = getchar()) != EOF) {
            putchar(toupper(current));
        }
    }

    return 0;
}