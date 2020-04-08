#ifndef TREE_H
#define TREE_H

#include "node.h"

node *insert_word(node *root, char *word);
void sort_words();
int node_comparator(node *node_1, node *node_2);
void print_distinct_words();

#endif