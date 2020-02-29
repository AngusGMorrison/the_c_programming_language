#include <stdio.h>

/**
 * Modify the temperature conversion program to print the table in reverse
 * order, that is, from 300 degress to 0.
 */

int main() {
    int lower = 0, upper = 300, step = 20;
    float fahr = upper, celsius;

    while (fahr >= 0) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr -= step;
    }
}