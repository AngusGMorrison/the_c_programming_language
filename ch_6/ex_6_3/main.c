/**
 * Write a cross-referencer that prints a list of all words in a document, and,
 * for each word, a list of the line numbers on which it occurs. Remove noise
 * words like "the", "and", and so on.
 */ 

#include <stdio.h>
#include "error.h"
#include "node.h"
#include "read_document.h"
#include "word_tree.h"

extern FILE* doc;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        arg_error("Usage: ./main <file path>");
    }

    if ((doc = fopen(argv[1], "r")) == NULL) {
        invalid_file_error("Unable to open file", argv[1]);
    }

    node *root = read_document();
    print_tree(root);
}