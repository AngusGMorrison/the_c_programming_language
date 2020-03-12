#include <stdio.h>
#include <limits.h>
#include <float.h>

/** Write a program to determine the ranges of char, short, int and long
 * variables, both signed and unsigned, by printing appropriate variables from
 * standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating point types.
 */

int main() {
    printf("limits.h\n");
    printf("char MIN\t%i\n", CHAR_MIN);
    printf("char MAX\t%i\n", CHAR_MAX);
    printf("schar MIN\t%i\n", SCHAR_MIN);
    printf("schar MAX\t%i\n", SCHAR_MAX);
    printf("uchar MAX\t%u\n", UCHAR_MAX);
    printf("short MIN\t%i\n", SHRT_MIN);
    printf("short MAX\t%i\n", SHRT_MAX);
    printf("ushort MAX\t%u\n", USHRT_MAX);
    printf("int MIN\t\t%i\n", INT_MIN);
    printf("int MAX\t\t%i\n", INT_MAX);
    printf("uint MAX\t%u\n", UINT_MAX);
    printf("long MIN\t%li\n", LONG_MIN);
    printf("long MAX\t%li\n", LONG_MAX);
    printf("ulong MAX\t%lu\n", ULONG_MAX);
    printf("flt MIN\t\t%f\n", FLT_MIN);
    printf("flt MAX\t\t%f\n", FLT_MAX);
    printf("dbl MIN\t\t%f\n", DBL_MIN);
    printf("dbl MAX\t\t%f\n\n", DBL_MAX);

    printf("Calculation\n");
    /* Invert all 8 possible bits of an unsigned char to 1 - this is the maximum
       value that can be stored in an unsiged char. A signed char uses the
       leftmost bit to store the sign, therefore the maximum value that can be
       stored in a signed char comes from shifting all the bits one place to the
       right, resulting in the loss of the rightmost bit but leaving space for
       the sign bit.

       To find the minimum unsigned char, subtract 1 (a quirk of the "one's
       complement approach) and make the resulting value negative. */
    printf("schar MIN\t%i\n", -((unsigned char) ~0 >> 1) - 1);
    printf("schar MAX\t%i\n", ((unsigned char) ~0 >> 1));
    printf("uchar MAX\t%i\n", (unsigned char) ~0);
    printf("short MIN\t%i\n", -((unsigned short) ~0 >> 1) - 1);
    printf("short MAX\t%i\n", ((unsigned short) ~0 >> 1));
    printf("ushort MAX\t%i\n", (unsigned short) ~0);
    printf("int MIN\t\t%i\n", -((unsigned int) ~0 >> 1) - 1);
    printf("int MAX\t\t%i\n", ((unsigned int) ~0 >> 1));
    printf("uint MAX\t%u\n", (unsigned int) ~0);
    printf("long MIN\t%li\n", -((unsigned long) ~0 >> 1) - 1);
    printf("long MAX\t%li\n", ((unsigned long) ~0 >> 1));
    printf("ulong MAX\t%lu\n", ((unsigned long) ~0));


    return 0;
}