/**
 * Define a macro swap(t, x, y) that interchanges two arguments of type t.
 * (Block structure will help)
 */

#include <stdio.h>

#define swap(t, x, y) { t temp; temp = x, x = y, y = temp; }

int main() {
    int x = 1;
    int y = 2;
    swap(int, x, y);
    printf("x: %i\ny: %i\n", x, y);
}