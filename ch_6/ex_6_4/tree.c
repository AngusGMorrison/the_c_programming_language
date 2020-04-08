/**
 * Handle node insertion and array operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "node.h"
#include "tree.h"

static int node_count = 0;

// Insert a word into the tree, or increment its count if already seen
node *insert_word(node *root, char *word) {
    int comp;

    if (root == NULL) {
        root = &word_arr[node_count++];
        root->word = word;
        root->count = 1;
    } else if ((comp = strcmp(root->word, word)) == 0) {
        ++root->count;
    } else if (comp < 0) {
        root->left = insert_word(root->left, word);
    } else {
        root->right = insert_word(root->right, word);
    }

    return root;
}

// Sort array of word nodes by decreasing frequencing of occurence
void sort_words() {
    qsort(
        word_arr,
        node_count,
        sizeof(node),
        (int (*) (const void*, const void*)) node_comparator
    );
}

// Compare two nodes by their words
int node_comparator(node *node_1, node *node_2) {
    return node_2->count - node_1->count;
}

// Print words and word counts in decreasing order
void print_distinct_words() {
    for (int i = 0; i < node_count; i++) {
        printf("%3i\t%s\n", word_arr[i].count, word_arr[i].word);
    }
}