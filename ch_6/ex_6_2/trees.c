/**
 * Define insert and print operations on match_node and word_node trees.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "trees.h"

extern int match_length;

// Add a variable name to the word tree under the correct match_node
match_node *insert_variable(match_node *root, char *variable) {
    int comparison;

    if (root == NULL) {
        root = match_node_alloc();
        root->match_string = get_match_string(variable);
        root->root_word = insert_matched_word(root->root_word, variable);
    } else if ((comparison = strncmp(variable, root->match_string, match_length)) == 0) {
        root->root_word = insert_matched_word(root->root_word, variable);
    } else if (comparison < 0) {
        root->left = insert_variable(root->left, variable);
    } else {
        root->right = insert_variable(root->right, variable);
    }

    return root;
}

// Return a pointer to a string containing the first X characters of variable
static char *get_match_string(char *variable) {
    char *match_string = malloc(match_length + 1);
    if (match_string == NULL) {
        null_pointer_error("match_string");
    }
    
    strncpy(match_string, variable, match_length);
    return match_string;
}

// Return a pointer to a new match_node with all fields initialized to null
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

/* Once a word is matched to a match_node, insert the word into the tree of
   words starting with match_node's match_string. */
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

// Return a pointer to a word_node with all fields initialized to null
static word_node *word_node_alloc() {
    word_node *new = malloc(sizeof(word_node));
    if (new == NULL) {
        null_pointer_error("new");
    }
    new->word = NULL;
    new->left = new->right = NULL;
    return new;
}

// Return a pointer to a copy of word
static char *str_dup(char *word) {
    char *copy = malloc(sizeof(*word));
    if (copy == NULL) {
        null_pointer_error("copy");
    }

    strcpy(copy, word);
    return copy;
}

// Print and error and exit if memory allocation fails
static void null_pointer_error(char *name) {
    printf("Error: null pointer '%s'\n", name);
    exit(4);
}

/* Print the entire match tree and each match_node's word tree in alphabetical
   order. */
void print_match_tree(match_node *root) {
    if (root != NULL) {
        print_match_tree(root->left);
        printf("Group: %s\n", root->match_string);
        print_word_tree(root->root_word);
        print_match_tree(root->right);
    }
}

// Print an entire word tree in alphabetical order
static void print_word_tree(word_node *root) {
    if (root != NULL) {
        print_word_tree(root-> left);
        printf("%s\n", root->word);
        print_word_tree(root->right);
    }
}