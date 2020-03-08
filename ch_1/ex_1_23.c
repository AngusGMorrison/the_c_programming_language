#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments do not
 * next.
 * 
 * For simplicity, this program uses only the official slash-star standard for
 * C comments.
 */

#define TEMPFILE "./test_data/temp"
#define ARG_ERROR "Usage: ./ex_1_23 <file path>.c\n"
#define ARG_ERROR_CODE 1
#define TEMP_ERROR "Failed to open temp file\n"
#define TEMP_ERROR_CODE 2
#define INPUT_ERROR "Failed to open input file\n"
#define INPUT_ERROR_CODE 3
#define INVALID_FILE_ERROR "File is not a valid C program\n"
#define INVALID_FILE_ERROR_CODE 4

int filter_comments(FILE *temp, char path[]);
int copy_temp(FILE *temp, char path[]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s", ARG_ERROR);
        return ARG_ERROR_CODE;
    }

    int arg_len = strlen(argv[1]);
    if (argv[1][arg_len-2] != '.' || argv[1][arg_len-1] != 'c') {
        printf("%s", ARG_ERROR);
        return ARG_ERROR_CODE;
    }

    FILE *temp = fopen(TEMPFILE, "w+");
    if (temp == NULL) {
        printf("%s", TEMP_ERROR);
        return TEMP_ERROR_CODE;
    }

    int filtered = filter_comments(temp, argv[1]);
    if (filtered != 0) {
        if (filtered == INPUT_ERROR_CODE) {
            printf("%s", INPUT_ERROR);
            return INPUT_ERROR_CODE;
        } else {
            printf("%s", INVALID_FILE_ERROR);
            return INVALID_FILE_ERROR_CODE;
        }
    }

    rewind(temp);
    int copied = copy_temp(temp, argv[1]);
    if (copied == INPUT_ERROR_CODE) {
        printf("%s", INPUT_ERROR);
        return INPUT_ERROR_CODE;
    }

    fclose(temp);
    remove(TEMPFILE);
    return 0;
}

/* Step through the input file, adding all characters to the temp file unless
   current within a comment. */
int filter_comments(FILE *temp, char path[]) {
    FILE *program = fopen(path, "r");
    if (program == NULL) return INPUT_ERROR_CODE;

    char prev_char = fgetc(program);
    if (prev_char == EOF) return INVALID_FILE_ERROR_CODE;

    char current_char;
    bool in_comment = false;

    while ((current_char = fgetc(program)) != EOF) {
        if (in_comment) {
            if (prev_char == '*' && current_char == '/') {
                in_comment = false;
                // Ensure '/' doesn't end up as prev_char
                current_char = fgetc(program);
            }
        } else {
            if (prev_char == '/' && current_char == '*') {
                in_comment = true;
            } else {
                fputc(prev_char, temp);    
            }
        }
        prev_char = current_char;
    }
    fputc(prev_char, temp);

    fclose(program);
    return 0;
}

/* Replace the contents of the original file with the contents of the filtered
   file. */
int copy_temp(FILE *temp, char path[]) {
    FILE *program = fopen(path, "w");
    if (program == NULL) return INPUT_ERROR_CODE;

    char current_char;
    while ((current_char = fgetc(temp)) != EOF) {
        fputc(current_char, program);
    }

    fclose(program);
    return 0;
}