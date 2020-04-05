#ifndef NODES_H
#define NODES_H

// #define MAX_VAR_LEN 31  // Longest allowable variable name in C

typedef struct word_node {
    char *word;
    struct word_node *left;
    struct word_node *right;
} word_node;

typedef struct match_node {
    char *match_string;
    struct word_node *root_word;
    struct match_node *left;
    struct match_node *right;
} match_node;

#endif