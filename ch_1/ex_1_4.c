#include <stdio.h>

/**
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 */

int main() {
    int lower = -20, upper = 150, step = 10;
    float celsius = lower, fahr;

    while(celsius <= upper)
    {
        fahr = (celsius / (5.0 / 9.0)) + 32.0;
        printf("%4.0f %5.1f\n", celsius, fahr);
        celsius += step;
    }
}
