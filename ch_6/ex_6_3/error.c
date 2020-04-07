/**
 * Error handling functions.
 */

#include <stdio.h>
#include <stdlib.h>

enum { ARG = 1, INVALID_FILE, NULL_POINTER, BUFFER_OVERFLOW };

void arg_error(char *message) {
    printf("%s\n", message);
    exit(ARG);
}

void invalid_file_error(char *message, char *filename) {
    printf("Error: %s %s\n", message, filename);
    exit(INVALID_FILE);
}

void null_pointer_error(char *pointer_name, char *func_name) {
    printf("Error: Null pointer '%s' in %s\n", pointer_name, func_name);
    exit(NULL_POINTER);
}

void buffer_overflow_error(char c) {
    printf("Error: '%c' overflowed the buffer\n", c);
    exit(BUFFER_OVERFLOW);
}