/**
 * Error handling functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

enum { NULL_POINTER = 1, BUFFER_OVERFLOW };

void null_pointer_error(char *pointer_name, char *func_name) {
    printf("Error: Null pointer '%s' in %s\n", pointer_name, func_name);
    exit(NULL_POINTER);
}

void buffer_overflow_error(char c) {
    printf("Error: '%c' overflowed the buffer\n", c);
    exit(BUFFER_OVERFLOW);
}