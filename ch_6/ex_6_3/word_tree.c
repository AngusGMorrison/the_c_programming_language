/**
 * Create and print a tree of nodes storing words and their line numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "error.h"
#include "word_tree.h"

node *insert_word(node *root, char *word, int line) {
    int comp;

    if (root == NULL) {
        root = node_alloc();
        root->word = word;
        root->line_nums[root->line_count++] = line;
    } else if ((comp = strcmp(word, root->word)) < 0) {
        root->left = insert_word(root->left, word, line);
    } else if (comp > 0) {
        root->right = insert_word(root->right, word, line);
    } else {
        if (word_already_on_line(line, root) == -1) {
            root->line_nums[root->line_count++] = line;
        }
    }

    return root;
}

static node *node_alloc() {
    node *new = malloc(sizeof(node));
    if (new == NULL) {
        null_pointer_error("new", "node_alloc");
    }

    new->word = NULL;
    new->line_count = 0;
    new->left = new->right = NULL;
    return new;
}

int word_already_on_line(int line, node *current_node) {
    int comparison, low, mid, high;

    low = 0;
    high = current_node->line_count - 1;

    while (low < high) {
        mid = (low + high) / 2;
        if ((comparison = line - current_node->line_nums[mid]) < 0) {
            high = mid - 1;
        } else if (comparison > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

void print_tree(node *root) {
    if (root == NULL) return;

    print_tree(root->left);
    printf("%-20s", root->word);
    print_line_nums(root->line_nums, root->line_count);
    printf("\n");
    print_tree(root->right);
}

void print_line_nums(int line_nums[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%i ", line_nums[i]);
    } 
}