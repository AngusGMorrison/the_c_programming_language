/**
 * Error handling functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

enum { ARGC = 1, FOPEN, OVERFLOW, NULL_PTR };

void argc_error() {
    printf("Usage: ./main <file path>\n");
    exit(ARGC);
}

void fopen_error(char *path) {
    printf("Error: unable to open file %s\n", path);
    exit(FOPEN);
}

void buffer_overflow_error(char overflow) {
    printf("Error: character '%c' overflowed the buffer\n", overflow);
    exit(OVERFLOW);
}

void null_pointer_error(char *p_name, char *func_name) {
    printf("Error: null pointer %s in function %s\n", p_name, func_name);
    exit(NULL_PTR);
}