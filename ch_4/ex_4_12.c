#include <stdio.h>
#include <stdlib.h>

/**
 * Adpat the ideas of printd to write a recursive version of itoa; that is,
 * convert an integer into a string by calling a recursive routine.
 */

int itoa(int i, char *a);

#define MAX_LEN 100

int main() {
    int i = -362;
    char a[MAX_LEN];
    itoa(i, a);
    printf("%s\n", a);
}

#define MAX_LEN 100

int itoa(int i, char *a) {
    int pos;

    if (i / 10) {
        // If the level of recursion hasn't yet reached the 1s column...
        pos = itoa(i / 10, a);
    } else {
        // Begin the string, with a sign char if needed
        pos = 0;
        if (i < 0) {
            a[pos++] = '-';
        } 
    }

    a[pos++] = abs(i) % 10 + '0';
    /* Terminate the string after each call; calls higher up the chain will
       simply overwrite the nul char if necessary. */
    a[pos] = '\0';
    /* Return the current index in the string so calls higher up the chain
       know where to insert. */
    return pos;
}