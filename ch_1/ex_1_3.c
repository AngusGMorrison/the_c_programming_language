#include <stdio.h>

/**
 * Modify the temperature conversion program to print a heading above the table.
 */

int main() {
    int lower = 0, upper = 300, step = 20;
    float fahr = lower, celsius;

    printf("%3s %6s\n", "F", "C");
    printf("----------\n");
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    }
}