#include <stdio.h>

/**
 * Reqire the temperature conversion program of Section 1.2 to use a function
 * for conversion.
 */

float f_to_c(int fahr);

int main() {
    int lower = 0, upper = 300, step = 20;
    float fahr = lower;

    while (fahr <= upper) {
        float celsius = f_to_c(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    }
}

float f_to_c(int fahr) {
    return (5.0 / 9.0) * (fahr - 32.0);
}