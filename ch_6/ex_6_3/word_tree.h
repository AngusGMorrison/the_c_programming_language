#ifndef WORD_TREE_H
#define WORD_TREE_H

#include "node.h"

node *insert_word(node *root, char *word, int line);
static node *node_alloc();
static int word_already_on_line(int line, node *current_node);
void print_tree(node *root);
void print_line_nums(int line_nums[], int count);

#endif