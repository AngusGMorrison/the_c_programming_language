/**
 * Read words and line numbers from a user-specified document ommitting noise
 * words like "the" and "and".
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "read_document.h"
#include "word_tree.h"

FILE *doc;
static int line_num = 1;
static char *noise_words[] = {
    "a",
    "an",
    "and",
    "are",
    "as",
    "at",
    "by",
    "for",
    "has",
    "i",
    "if",
    "in",
    "is",
    "it",
    "its",
    "of",
    "on",
    "the",
    "to",
    "too",
    "was",
    "we",
    "you"
};
static int noise_word_count = sizeof(noise_words) / sizeof(char *);

node *read_document() {
    char *word;
    node *root = NULL;

    while ((word = get_word()) != NULL) {
        *word = tolower(*word);
        if (is_noise_word(word) == -1) {
            root = insert_word(root, word, line_num);
        }
    }

    return root;
}

#define MAX_LINE 1000
#define MAX_WORD 50

static char *get_word() {
    char current, word[MAX_WORD];
    int pos = 0;

    while (!isalpha(current = getch())) {
        if (current == '\n') {
            line_num++;
        } else if (current == EOF) {
            return NULL;
        }
    }

    word[pos++] = current;
    while (isalpha(current = getch())) {
        word[pos++] = current;
    }

    if (current == '\n') {
        line_num++;
    } else {
        ungetch(current);
    }

    word[pos++] = '\0';
    return duplicate(word);
}

static char *duplicate(char *word) {
    char *copy = malloc(strlen(word) + 1);
    if (copy == NULL) {
        null_pointer_error("copy", "duplicate");
    }

    strcpy(copy, word);
    return copy;
}

#define MAX_BUF 10
static char buffer[MAX_BUF];
static int buf_pos = 0;

static char getch() {
    return buf_pos > 0 ? buffer[--buf_pos] : fgetc(doc);
}

static void ungetch(char c) {
    if (buf_pos < MAX_BUF - 1) {
        buffer[buf_pos++] = c;
    } else {
        buffer_overflow_error(c);
    }
}

int is_noise_word(char *word) {
    int comparison, mid;
    int low = 0;
    int high = noise_word_count - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((comparison = strcmp(word, noise_words[mid])) < 0) {
            high = mid - 1;
        } else if (comparison > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}


