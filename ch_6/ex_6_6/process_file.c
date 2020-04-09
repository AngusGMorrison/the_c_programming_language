/**
 * Process tokens from a C file.
 * 
 * This implementation could be extended to account for comments and string
 * literals.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "hash_table.h"
#include "process_file.h"

#define MAX_WORD 50

const int HASH_SIZE = 101;
static node *definitions[HASH_SIZE];

FILE *in, *out;

/* Identify whether the token produced by get_token is a symbol like ' ' or '(',
   a preprocessing flag or a full word. */
enum { FLAG, WORD };
static int token_type;

void process_file() {
    char token[MAX_WORD], *key, *value;
    node *match;

    while ((token_type = get_next_token(token)) != EOF) {
        if (token_type == FLAG) {
            if (strcmp(token, "#define") == 0) {
                fprintf(out, "%s", token);
                get_next_token(token);
                key = str_dup(token);
                fprintf(out, "%s", key);
                get_next_token(token);
                value = str_dup(token);
                install(definitions, key, value);
                fprintf(out, "%s", value);
            } else {
                fprintf(out, "%s", token);
            }
        } else {
            if ((match = lookup(definitions, token)) != NULL) {
                fprintf(out, "%s", match->value);
            } else {
                fprintf(out, "%s", token);
            }    
        }
    }

    fclose(in);
    fclose(out);
}

// Reads input to output file until it encounters a word or preprocessor flag
int get_next_token(char *token) {
    char *ptoken = token;
    char current;

    while ((current = get_char()) != EOF && !isalnum(current) && current != '#') {
        fprintf(out, "%c", current);
    }
    
    if (current == EOF) {
        return EOF;
    }

    *ptoken++ = current;
    if (current == '#') {
        while (isalnum(current = get_char())) {
            *ptoken++ = current;
        }
        unget_char(current);
        *ptoken = '\0';
        return token_type = FLAG;
    } else {
        while (isalnum(current = get_char()) || current == '_') {
            *ptoken++ = current;
        }
        unget_char(current);
        *ptoken = '\0';
        return token_type = WORD;
    }

    return EOF;
}

// Buffer operations
#define MAX_BUF 10
static char buffer[MAX_BUF];
static int buf_pos = 0;

static char get_char() {
    return buf_pos > 0 ? buffer[--buf_pos] : fgetc(in);
}

static void unget_char(char c) {
    if (buf_pos < MAX_BUF - 1) {
        buffer[buf_pos++] = c;
    } else {
        buffer_overflow_error(c);
    }
}

static char *str_dup(char *str) {
    char *copy = malloc(strlen(str) + 1);
    if (copy == NULL) {
        null_pointer_error("copy", "str_dup");
    }

    strcpy(copy, str);
    return copy;
}

