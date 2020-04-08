#ifndef NODE_H
#define NODE_H

#define MAX_WORDS 1000

typedef struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
} node;

node word_arr[MAX_WORDS];

#endif