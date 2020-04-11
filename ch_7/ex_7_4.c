/**
 * Write a private version of scanf analogous to minprintf from the previous
 * section.
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 1000
#define MAX_TOKEN 100

int minscanf(char *fmt, ...);
int get_input(char *input, int max_len);
char *get_next_token(char *token, char *input);

int main() {
    int i;
    double f;
    char s[MAX_TOKEN];
    minscanf("%i %f %s", &i, &f, s);
    printf("%i %f %s\n", i, f, s);
}

int minscanf(char *fmt, ...) {
    va_list arg_ptr;
    int tokens_matched;
    char *fmt_ptr, *sval, input[MAX_INPUT], *input_pos, token[MAX_TOKEN], *token_ptr;

    get_input(input, MAX_INPUT);
    input_pos = input;
    va_start(arg_ptr, fmt);
    tokens_matched = 0;

    for (fmt_ptr = fmt; *fmt_ptr; fmt_ptr++) {
        if (!*(input_pos = get_next_token(token, input_pos))) {
            break;
        }

        while (isspace(*fmt_ptr)) {
            fmt_ptr++;
        }

        if (*fmt_ptr != '%') {
            return tokens_matched;
        }

        switch (*++fmt_ptr) {
            case 'i':
            case 'd':
                *va_arg(arg_ptr, int *) = atoi(token); 
                tokens_matched++;
                break;
            case 'f':
                *va_arg(arg_ptr, double *) = atof(token); 
                tokens_matched++;
                break;
            case 's':
                token_ptr = token;
                sval = va_arg(arg_ptr, char *);
                while (*token_ptr != '\0') {
                    *sval++ = *token_ptr++;
                }
                *sval = '\0';
                tokens_matched++;
                break;
            default:
                printf("Unknown format character: %c", *fmt_ptr);
                return tokens_matched;
        }
    }

    va_end(arg_ptr);
    return tokens_matched;
}

// Get user input as single string
int get_input(char *input, int max_len) {
    char current;
    char *input_ptr = input;
    int len = 0;

    while ((current = getchar()) != EOF && len < max_len) {
        *input_ptr++ = current;
        len++;
    }
    
    *input_ptr = '\0';
    return len;
}

// Get the next contiguous block of non-whitespace characters from input
char *get_next_token(char *token, char *input) {
    char current;
    char *token_ptr = token;

    for ( ; isspace(*input); input++)
        ;

    *token_ptr++ = *input;
    while (*++input && !isspace(*input)) {
        *token_ptr++ = *input;
    }
    *token_ptr = '\0';
    return input;
}