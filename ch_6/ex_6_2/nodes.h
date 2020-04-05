#ifndef NODES_H
#define NODES_H

// #define MAX_VAR_LEN 31  // Longest allowable variable name in C

// Holds a single variable name and points to left and right children
typedef struct word_node {
    char *word;
    struct word_node *left;
    struct word_node *right;
} word_node;

/* Holds the first X characters by which variable names are categorised, and
   a pointer the root node of a tree containing all words starting with
   match_string. */
typedef struct match_node {
    char *match_string;
    struct word_node *root_word;
    struct match_node *left;
    struct match_node *right;
} match_node;

#endif