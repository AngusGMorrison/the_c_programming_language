#ifndef NODE_H
#define NODE_H

#define MAX_LINE_NUMS 1000

typedef struct node {
    char *word;
    int line_count;
    int line_nums[MAX_LINE_NUMS];
    struct node *left;
    struct node *right;
} node;

#endif