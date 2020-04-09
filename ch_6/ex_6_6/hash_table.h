#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct node {
    char *key;
    char *value;
    struct node *next;
} node;

node *lookup(node *table[], char *key);
node *install(node *table[], char *key, char *value);
static unsigned hash(char *key);
static node *alloc_node();

#endif