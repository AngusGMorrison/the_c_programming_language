#include <ctype.h>
#include <math.h>
#include <stdio.h>

/**
 * Extend atof to handle scientific notation of the form 123.45e-6 where a
 * floating point number may be followed by e or E and an optionally signed
 * exponent.
 */ 

double atof(char s[]);
int get_exponent(char s[], int i);

int main() {
    char decimal[] = "123.456E-7";
    double dubbed = atof(decimal);
    printf("%f\n", dubbed);
    printf("%f\n", 123.456E-7);
    printf("%i\n", dubbed == 123.456E-7);
}

double atof(char s[]) {
    double val, power;
    int i, sign, exp;

    // Skip whitespace
    for (i = 0; isspace(s[i]); i++)
        ; 

    // Save sign and skip the char
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    // Calculate number before decimal point
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    
    // Skip the decimal point
    if (s[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    exp = get_exponent(s, i);
    return (sign * val / power) * pow(10.0, exp);
}

int get_exponent(char s[], int i) {
    // Exp will be 0 if there is no exponent sign. 10 ^ 0 == 1.
    int exp = 0;
    // Check for exponent sign
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        // Record the sign and move past the sign char, if there is one
        int sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') {
            i++;
        }
        // Include each digit in the exponent
        while (isdigit(s[i])) {
            exp = 10 * exp + (s[i] - '0');
            i++;
        }
        // Make exp negative as appropriate
        exp *= sign;
    }
    return exp;
}