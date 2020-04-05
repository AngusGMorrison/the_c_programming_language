/**
 * Write a program that reads a C program and prints in alphabetical order
 * each group of variable names that are identical in the first 6 characters,
 * but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "read_variables.h"
#include "trees.h"

match_node *group_variables();

extern FILE* program;
int match_length;
extern const int MAX_VAR_LEN;

int main(int argc, char *argv[]) {
    // Read command line args and open file for reading
    if (argc != 3) {
        printf("Usage: ./ex_6_2 <file_path> <match_length>\n");
        return 1;
    }

    if ((program = fopen(argv[1], "r")) == NULL) {
        printf("Error: couldn't open file at %s\n", argv[1]);
        return 2;
    }
    
    match_length = atoi(argv[2]);

    // Read file variables into match_node tree
    match_node *root = group_variables();
    print_match_tree(root);
    fclose(program);

    return 0;
}

/* Add each variable to the tree match_node with the corresponding match_string,
   creating the match_node if it doesn't yet exist. */
match_node *group_variables() {
    char variable[MAX_VAR_LEN];
    match_node *root = NULL;

    while (get_variable(variable) != EOF) {
        root = insert_variable(root, variable);
    }

    return root;
}
