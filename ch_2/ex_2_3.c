#include <stdio.h>
#include <string.h>

/**
 * Write the function htoi(s), which converts a string of hexadecial digits
 * (including an optional 0x or 0X) into its equivalent integer value. The
 * allowable digits are 0 through 9, a through f, and A through F.
 */

int htoi(char s[]);

int main() {
    printf("%i\n", htoi("0x9"));
    printf("%i\n", htoi("0x16"));
    printf("%i\n", htoi("0xF"));
    printf("%i\n", htoi("0xFF"));
    printf("%i\n", htoi("0xD6A"));
}

int htoi(char s[]) {
    int i = 0;
    int len = strlen(s);
    int output = 0;

    // Skip 0x/0X, if present
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }
    
    for (; i < len; i++) {
        int val;

        if (s[i] >= '0' && s[i] <= '9') {
            val = s[i] - '0';
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            val = s[i] - 'A' + 10;
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            val = s[i] - 'a' + 10;
        } else {
            return -1;
        }

        output = output * 16 + val;
    }
    return output;
}