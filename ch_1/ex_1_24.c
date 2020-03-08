#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Write a program to check a C program for rudimentary syntax errors like
 * unbalanced parentheses, brackets and braces. Don't forget about quotes, both
 * single and double, escape sequences, and comments. (This program is hard
 * if you do it in full generality.)
 * 
 * Note: This version checks for unmatches brackets outside of comments and
 * parentheses, and escape sequences outside of string literals.
 */

#define ARG_ERR "Usage: ./ex_1_24 <filepath>.c\n"
#define ARG_ERR_CODE 1
#define FILE_ERR "Failed to open file\n"
#define FILE_ERR_CODE 2

#define STACK_DEPTH 20

int l_brackets[STACK_DEPTH];
int depth = 0;
int line = 1;

char get_char_check_line(FILE *program);
void in_comment(FILE *program);
void in_quotes(FILE *program, char openquote);
bool bracket_unmatched(char c);
bool escape_not_valid(char c);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s", ARG_ERR);
        return ARG_ERR_CODE;
    }

    int arg_len = strlen(argv[1]);
    if (arg_len < 3 || argv[1][arg_len - 2] != '.' || argv[1][arg_len - 1] != 'c') {
        printf("%s", ARG_ERR);
        return ARG_ERR_CODE;
    }

    FILE *program = fopen(argv[1], "r");
    if (program == NULL) {
        printf("%s", FILE_ERR);
        return FILE_ERR_CODE;
    }

    // Use a rudimentary stack to to track open parentheses
    
    char c;
    while ((c = get_char_check_line(program)) != EOF) {
        // Skip over comments
        if (c == '/' && (c = get_char_check_line(program) == '*')) {
            in_comment(program);
        }
        // Skip over quoted strings
        if (c == '\'' || c == '"') {
            in_quotes(program, c);
        }
        // Check brackets are paired and there no escapes outside strings
        if (bracket_unmatched(c) || escape_not_valid(c)) {
            fclose(program);
            return 0;
        }
    }

    printf("Looks good!\n");
    return 0;
}

// While inside a comment, prevent other syntax checks until comment ends
void in_comment(FILE *program) {
    char prev = get_char_check_line(program);
    char next = get_char_check_line(program);

    while (prev != '*' || next != '/') {
        prev = next;
        next = get_char_check_line(program);
    }
}

// While inside quotes, prevent other syntax checks until quotes are closed
void in_quotes(FILE *program, char openquote) {
    char next;
    while ((next = get_char_check_line(program)) != openquote) {
        if (next == '\\') {
            // Skip whatever character has been escaped
            get_char_check_line(program);
        }
    }
}

/* Ensures line count is always incremented when multiple chars are read in
   a single loop (e.g. when checking comment boundaries). */
char get_char_check_line(FILE *program) {
    char c = fgetc(program);
    if (c == '\n') {
        line++;
    }
    return c;
}

// Use a rudimentary stack to ensure all brackets are matched
bool bracket_unmatched(char c) {
    if (c == '(' || c == '[' || c == '{') {
        l_brackets[depth++] = c;
    } else if (c == ')' || c == ']' || c == '}') {
        /* For ] and }, their left-facing partners are 2 ASCII characters less
           than them, hence c - 2. */
        if (depth == 0 || (l_brackets[depth - 1] != '(' && l_brackets[depth - 1] != (c - 2))) {
            printf("Line %i: unmatched %c\n", line, c);
            return true;
        } else {
            depth--;
        }
    }
    return false;
}

// Any backslash outside a string literal is considered invalid
bool escape_not_valid(char c) {
    if (c =='\\') {
        printf("Line %i: invalid escape sequence\n", line);
        return true;
    }
    return false;
}