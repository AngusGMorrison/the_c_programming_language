#include <stdio.h>

/**
 * In a two's complement number system, x &= (x - 1) deletes the rightmost 1-bit
 * in x. Explain why. Use this observation to write a faster version of
 * bitcount.
 * 
 * Explanation: As 1 is the largest value that can be represented in a single
 * bit, x - 1 must necessarily have 1 bit less than x. Therefore, the right-most
 * bit (which represents the value 1) will always be different in x and x - 1.
 * Because they differ, using & will always set the right-most bit to 0.
 */

int bitcount(unsigned x) {
    int count;
    while (x != 0) {
        x &= x - 1;
        count++;
    };
    return count;
}

