/**
 * Write a program that reads a C program and prints in alphabetical order
 * each group of variable names that are identical in the first 6 characters,
 * but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 * 
 * Currently treats function declarations the same as variable declarations.
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

typedef struct word_node {
    char *word;
    struct word_node *left;
    struct word_node *right;
} word_node;

typedef struct match_node {
    char *match_string;
    struct word_node *root_word;
    struct match_node *left;
    struct match_node *right;
} match_node;

match_node *group_variables();
void print_match_tree(match_node *root);

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
    
    match_length = atoi(argv[2]);

    // Read file variables into match_node tree
    match_node *root = group_variables();
    fclose(program);
    print_match_tree(root);
    
    return 0;
}

int get_variable(char *variable);
int get_word(char *word, int limit);
int binsearch(char *key, char *table[], int nkeys);
match_node *insert_variable(match_node* root, char *var);

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

int get_variable(char *variable) {
    int declaration = 0;     // Flag a variable declaration for capture
    char word[MAX_VAR_LEN];

    while (get_word(word, MAX_VAR_LEN) != EOF) {
        if (declaration) {
            // Account for pointers and two-word types like long double
            if (word[0] != '*' && binsearch(word, types, NTYPES) < 0) {
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

match_node *match_node_alloc();
char *get_match_string(char *variable);
word_node *insert_matched_word(word_node *root, char *variable);
word_node *word_node_alloc();
char *str_dup(char *word);
void null_pointer_error(char *name);

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

char *get_match_string(char *variable) {
    char *match_string = malloc(match_length + 1);
    if (match_string == NULL) {
        null_pointer_error("match_string");
    }
    
    strncpy(match_string, variable, match_length);
    return match_string;
}

match_node *match_node_alloc() {
    match_node *new = malloc(sizeof(match_node));
    if (new == NULL) {
        null_pointer_error("new");
    }

    new->match_string = NULL;
    new->root_word = NULL;
    new->left = new->right = NULL;
    return new;
}

word_node *insert_matched_word(word_node *root, char *word) {
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

word_node *word_node_alloc() {
    word_node *new = malloc(sizeof(word_node));
    if (new == NULL) {
        null_pointer_error("new");
    }
    new->word = NULL;
    new->left = new->right = NULL;
    return new;
}

char *str_dup(char *word) {
    char *copy = malloc(sizeof(*word));
    if (copy == NULL) {
        null_pointer_error("copy");
    }

    strcpy(copy, word);
    return copy;
}

void null_pointer_error(char *name) {
    printf("Error: null pointer '%s'\n", name);
    exit(4);
}

void print_word_tree(word_node *root);

void print_match_tree(match_node *root) {
    if (root != NULL) {
        print_match_tree(root->left);
        printf("Group: %s\n", root->match_string);
        print_word_tree(root->root_word);
        print_match_tree(root->right);
    }
}

void print_word_tree(word_node *root) {
    if (root != NULL) {
        print_word_tree(root-> left);
        printf("%s\n", root->word);
        print_word_tree(root->right);
    }
}