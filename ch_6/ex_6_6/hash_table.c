/**
 * Perform hash table operations
 */ 

#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "hash_table.h"

extern const int HASH_SIZE;

node *lookup(node *table[], char *key) {
    node *match;
    for (match = table[hash(key)]; match != NULL; match = match->next) {
        if (strcmp(match->key, key) == 0) {
            return match;
        }
    }
    return NULL;
}

node *install(node *table[], char *key, char *value) {
    node *match;
    if ((match = lookup(table, key)) == NULL) {
        
        match = alloc_node();
        match->key = key;
        unsigned hashval = hash(key);
        match->next = table[hashval];
        table[hashval] = match;
    } else {
        free(match->value);
    }

    match->value = value;
    return match;
}

// Hash the value of key into a table index
static unsigned hash(char *key) {
    unsigned hashval;
    
    for (hashval = 0; *key != '\0'; key++) {
        hashval = *key + 31 * hashval;
    }

    return hashval % HASH_SIZE;
}

static node *alloc_node() {
    node *new = malloc(sizeof(node));
    
    if (new == NULL) {
        null_pointer_error("new", "alloc_node");
    }

    return new;
}