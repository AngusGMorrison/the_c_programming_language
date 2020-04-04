/**
 * Write a program that reads a C program and prints in alphabetical order
 * each group of variable names that are identical in the first 6 characters,
 * but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 * 
 * Doesn't currently handle pointers, and treats function declarations the
 * same as variable declarations.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAR_LEN 31  // Longest allowable variable name in C
#define MAX_VARS 1000   // Maximum variables matching each pattern

// Define valid types used to detect variable declarations
#define NTYPES 7
static char *types[] = {
    "char",
    "double",
    "float",
    "int",
    "long",
    "short",
    "void"
};

typedef struct node {
    char match_string[MAX_VAR_LEN];
    char *matches[MAX_VARS];
} node;

node *group_variables();

static FILE* program;
static int match_length;

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
    
    match_length = *argv[2];

    // Read file variables into node tree
    node *root = group_variables();

}

int get_variable(char *variable);
int get_word(char *word, int limit);
int binsearch(char *key, char *table[], int nkeys);
// node *insert_variable(node* root, char *var);

/* Add each variable to the tree node with the corresponding match_string,
   creating the node if it doesn't yet exist. */
node *group_variables() {
    char variable[MAX_VAR_LEN];
    char *temp_pointers[] = { "hello", "world" };
    node *root = malloc(sizeof(node));

    while (get_variable(variable) != EOF) {
        // printf("%s\n", variable);
        // root = insert_variable(root, variable);
    }

    return root;
}

int get_variable(char *variable) {
    int declaration = 0;     // Flag a variable declaration for capture
    char word[MAX_VAR_LEN];

    while (get_word(word, MAX_VAR_LEN) != EOF) {
        if (declaration) {
            // Account for pointers and two-word types like long double
            if (word[0] != '*' && binsearch(word, types, NTYPES) < 0) {
                printf("%s\n", word);
                strcpy(variable, word);
                declaration = 0;
                return 1;
            }
        } else {
            declaration = (binsearch(word, types, NTYPES) >= 0) ? 1 : 0;
        }
    }
    
    return EOF;
}

int get_word(char *word, int limit) {
    int getch();
    void ungetch(int c);

    int current, next;
    char *pword = word;

    while (isspace(current = getch()))
        ;
    
    if (!isalpha(current) && current != '"' && current != '/') {
        *pword++ = current;
        *pword = '\0';
        return current;
    }

    if (current == '"') {
        while ((current = getch()) != '"')
            ;
    }
    
    if (current == '/') {
        if ((next = getch()) == '*') {
            while (current != '*' || next != '/') {
                current = next;
                next = getch();
            }
            current = next;
        } else {
            ungetch(next);
        }
    }

    *pword++ = current;
    for ( ; --limit - 1; pword++) {
        if (!isalnum(*pword = getch()) && *pword != '_') {
            ungetch(*pword);
            break;
        }
    }

    *pword = '\0';
    return word[0];
}

#define BUF_SIZE 10
static int buffer[BUF_SIZE];
static int buf_pos = 0;

int getch() {
    return buf_pos > 0 ? buffer[--buf_pos] : fgetc(program);
}

void ungetch(int c) {
    if (buf_pos < BUF_SIZE - 1) {
        buffer[buf_pos++] = c;
    } else {
        printf("Error: buffer full");
        exit(3);
    }
}

int binsearch(char *key, char *table[], int nkeys) {
    int comparison, low, mid, high;

    low = 0;
    high = nkeys - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((comparison = strcmp(key, table[mid])) < 0) {
            high = mid - 1;
        } else if (comparison > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}