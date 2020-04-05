/**
 * Define insert and print operations on match_node and word_node trees.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "trees.h"

extern int match_length;

match_node *insert_variable(match_node *root, char *variable) {
    int comparison;

    if (root == NULL) {
        root = match_node_alloc();
        root->match_string = get_match_string(variable);
        root->root_word = insert_matched_word(root->root_word, variable);
    } else if ((comparison = strncmp(variable, root->match_string, match_length)) == 0) {
        // The variable starts with the same x letters as the current node
        root->root_word = insert_matched_word(root->root_word, variable);
    } else if (comparison < 0) {
        root->left = insert_variable(root->left, variable);
    } else {
        root->right = insert_variable(root->right, variable);
    }

    return root;
}

static char *get_match_string(char *variable) {
    char *match_string = malloc(match_length + 1);
    if (match_string == NULL) {
        null_pointer_error("match_string");
    }
    
    strncpy(match_string, variable, match_length);
    return match_string;
}

static match_node *match_node_alloc() {
    match_node *new = malloc(sizeof(match_node));
    if (new == NULL) {
        null_pointer_error("new");
    }

    new->match_string = NULL;
    new->root_word = NULL;
    new->left = new->right = NULL;
    return new;
}

static word_node *insert_matched_word(word_node *root, char *word) {
    int comparison;

    if (root == NULL) {
        root = word_node_alloc();
        root->word = str_dup(word);
    } else if ((comparison = strcmp(word, root->word)) < 0) {
        root->left = insert_matched_word(root->left, word);
    } else if (comparison > 0) {
        root->right = insert_matched_word(root->right, word);
    }
    return root;
}

static word_node *word_node_alloc() {
    word_node *new = malloc(sizeof(word_node));
    if (new == NULL) {
        null_pointer_error("new");
    }
    new->word = NULL;
    new->left = new->right = NULL;
    return new;
}

static char *str_dup(char *word) {
    char *copy = malloc(sizeof(*word));
    if (copy == NULL) {
        null_pointer_error("copy");
    }

    strcpy(copy, word);
    return copy;
}

static void null_pointer_error(char *name) {
    printf("Error: null pointer '%s'\n", name);
    exit(4);
}

void print_match_tree(match_node *root) {
    if (root != NULL) {
        print_match_tree(root->left);
        printf("Group: %s\n", root->match_string);
        print_word_tree(root->root_word);
        print_match_tree(root->right);
    }
}

static void print_word_tree(word_node *root) {
    if (root != NULL) {
        print_word_tree(root-> left);
        printf("%s\n", root->word);
        print_word_tree(root->right);
    }
}