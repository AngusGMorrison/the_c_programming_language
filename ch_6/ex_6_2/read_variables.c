/**
 * Read variable and function names from a C file.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_variables.h"

// Define valid types used to detect variable declarations
#define NTYPES 7
const char *types[] = {
    "char",
    "double",
    "float",
    "int",
    "long",
    "short",
    "void"
};

const int MAX_VAR_LEN = 31;
FILE *program;

// Extract variable and function names from a file
int get_variable(char *variable) {
    int declaration = 0;     // Flag a variable declaration for capture
    char word[MAX_VAR_LEN];

    while (get_word(word, MAX_VAR_LEN) != EOF) {
        if (declaration) {
            /* The preceding word was a variable declaration; check that the
               declaration is not two words (e.g. long double), then capture the
               word. */
            if (word[0] != '*' && binsearch(word, types, NTYPES) < 0) {
                strcpy(variable, word);
                declaration = 0;
                return 1;
            }
        } else {
            declaration = (binsearch(word, types, NTYPES) >= 0) ? 1 : 0;
        }
    }
    
    return EOF;
}

// Extract whole words from a file, excluding comments and string literals
static int get_word(char *word, int limit) {
    int getch();
    void ungetch(int c);

    int current, next;
    char *pword = word;

    while (isspace(current = getch()))
        ;
    
    if (!isalpha(current) && current != '"' && current != '/') {
        *pword++ = current;
        *pword = '\0';
        return current;
    }

    if (current == '"') {
        while ((current = getch()) != '"')
            ;
    }
    
    if (current == '/') {
        if ((next = getch()) == '*') {
            while (current != '*' || next != '/') {
                current = next;
                next = getch();
            }
            current = next;
        } else {
            ungetch(next);
        }
    }

    *pword++ = current;
    for ( ; --limit - 1; pword++) {
        if (!isalnum(*pword = getch()) && *pword != '_') {
            ungetch(*pword);
            break;
        }
    }

    *pword = '\0';
    return word[0];
}

#define BUF_SIZE 10
static int buffer[BUF_SIZE];
static int buf_pos = 0;

static int getch() {
    return buf_pos > 0 ? buffer[--buf_pos] : fgetc(program);
}

static void ungetch(int c) {
    if (buf_pos < BUF_SIZE - 1) {
        buffer[buf_pos++] = c;
    } else {
        printf("Error: buffer full");
        exit(3);
    }
}

// Binary search for valid data type matching key
static int binsearch(char *key, const char *table[], int nkeys) {
    int comparison, low, mid, high;

    low = 0;
    high = nkeys - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((comparison = strcmp(key, table[mid])) < 0) {
            high = mid - 1;
        } else if (comparison > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}