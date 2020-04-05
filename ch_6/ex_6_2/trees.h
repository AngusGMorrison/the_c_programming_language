#ifndef TREES_H
#define TREES_H

#include "nodes.h"

match_node *insert_variable(match_node *root, char *variable);
static match_node *match_node_alloc();
static char *get_match_string(char *variable);
static word_node *insert_matched_word(word_node *root, char *variable);
static word_node *word_node_alloc();
static char *str_dup(char *word);
static void null_pointer_error(char *name);
void print_match_tree(match_node *root);
static void print_word_tree(word_node *root);

#endif