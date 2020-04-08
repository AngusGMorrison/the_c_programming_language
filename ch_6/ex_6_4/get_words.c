/**
 * Get and count distinct words from user input, storing them in a tree of
 * nodes, which are themselves stored in an array for sorting.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "get_words.h"
#include "node.h"
#include "tree.h"

void get_distinct_words() {
    char *word;
    node *root = NULL;

    while ((word = get_word()) != NULL) {
        root = insert_word(root, word);
    }
}

#define MAX_WORD 50

char *get_word() {
    char current;
    char word[MAX_WORD];
    int pos = 0;

    while (!isalpha(current = getch()) && current != EOF)
        ;

    if (current == EOF) {
        return NULL;
    }

    word[pos++] = current;
    while (isalpha(current = getch()) || current == '\'' || current == '-') {
        word[pos++] = current;
    }
    ungetch(current);
    word[pos] = '\0';

    return str_dup(word);
}

char *str_dup(char *str) {
    char *copy = malloc(strlen(str) + 1);
    if (copy == NULL) {
        null_pointer_error("copy", "str_dup");
    }

    strcpy(copy, str);
    return copy;
}

#define MAX_BUF 10
char buffer[MAX_BUF];
int buf_pos = 0;

char getch() {
    return buf_pos > 0 ? buffer[--buf_pos] : getchar();
}

void ungetch(char c) {
    if (buf_pos < MAX_BUF - 1) {
        buffer[buf_pos++] = c;
    } else {
        buffer_overflow_error(c);
    }
}
