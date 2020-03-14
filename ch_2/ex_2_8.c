#include <stdio.h>

/**
 * Write a function rightrot(x, n) that returns the value of the integer x
 * rotated to the right by n bit positions.
 */

/* The number of bits your system uses to represent an integer. This can also
   be calculated (see ex_2_9). */
#define INT_BITS 32

int rightrot(int x, int n);

int main() {
    int x = 10;
    x = rightrot(x, 3);
    printf("%i\n", x);
}

int rightrot(int x, int n) {
    // Save the n bits at the right had side of x
    unsigned saved = x & ~(~0 << n);
    // Left-shift the saved bits to the end of the integer
    saved = saved << (INT_BITS - n);
    // Right shift x, cutting off the bits that we saved
    x = x >> n;     
    // Switch on the saved bits at the left-hand side of x                    
    return x | saved;
}