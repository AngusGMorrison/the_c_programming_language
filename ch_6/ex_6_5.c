/**
 * Write a function undef that will remove a name and definition from the table
 * maintained by lookup and install.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *name;
    char *defn;
    struct node *next;
} node;

unsigned hash(char *s);
node *lookup(char *s);
node *install(char *name, char *defn);
char *str_dup(char *s);
void undef(char *name);

int main() {
    install("Bianca", "Bass");
    install("Angus", "Morrison");
    printf("%s\n", lookup("Bianca")->defn);
    printf("%s\n", lookup("Angus")->defn);
    undef("Angus");
    if (lookup("Angus") == NULL) {
        printf("Undef'd Angus\n");
    }
}

#define HASHSIZE 101

static node *table[HASHSIZE];

// Create hash value for string
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

// Look for s in table
node *lookup(char *name) {
    node *match;

    for (match = table[hash(name)]; match != NULL; match = match->next) {
        if (strcmp(name, match->name) == 0) {
            return match;
        }
    }

    return NULL;
}

// Put (name, defn) in table
node *install(char *name, char *defn) {
    node *target;
    unsigned hashval;

    if ((target = lookup(name)) == NULL) {
        target = malloc(sizeof(node));
        if (target == NULL || (target->name = str_dup(name)) == NULL) {
            printf("Null pointer error");
            return NULL;
        }
        hashval = hash(name);
        target->next = table[hashval];
        table[hashval] = target;
    } else {
        // Key already exists; free old definition before redefining
        free(target->defn);
    }

    if ((target->defn = str_dup(defn)) == NULL) {
        printf("Null pointer error");
        return NULL;
    }

    return target;
}

char *str_dup(char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (copy == NULL) {
        printf("Null pointer error");
        return NULL;
    }
    
    return strcpy(copy, s);
}

void undef(char *name) {
    node *match;

    if ((match = lookup(name)) == NULL) return;

    table[hash(name)] = match->next;
    free(match->name);
    free(match->defn);
    free(match);
}


