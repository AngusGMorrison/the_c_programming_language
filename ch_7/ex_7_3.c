/**
 * Revise minprintf to handle more of the other facilities of printf.
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void minprintf(char *fmt, ...);
void print_padded_string(char *sval, int padding, int left_align);

int main() {
    minprintf("Printing test string %d: %5s\n", 1, "Angus");
    return 0;
}

// Minimal printf with variable argument list
void minprintf(char *fmt, ...) {
    va_list arg_ptr;    // Points to each unnamed arg in turn
    char *fmt_ptr, *sval;
    int ival, padding, left_align;
    double dval;

    va_start(arg_ptr, fmt);     // Make arg_ptr point to first unnamed arg
    for (fmt_ptr = fmt; *fmt_ptr; fmt_ptr++) {
        if (*fmt_ptr != '%') {
            putchar(*fmt_ptr);
            continue;
        }

        // Handle padding
        left_align = 0;
        padding = 0;

        if (*(fmt_ptr + 1) == '-') {
            left_align = 1;
            fmt_ptr++;
        }

        while (isdigit(*++fmt_ptr)) {
            padding = (padding * 10) + (*fmt_ptr - '0');
        }
        
        switch (*fmt_ptr) {
            case 'd':
                ival = va_arg(arg_ptr, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(arg_ptr, double);
                printf("%f", dval);
                break;
            case 's':
                sval = va_arg(arg_ptr, char *);
                print_padded_string(sval, padding, left_align);
                break;
            default:
                putchar(*fmt_ptr);
                break;
        }
    }

    va_end(arg_ptr);    // Clean up when done
}

void print_padded_string(char *sval, int padding, int left_align) {
    int req_padding = padding - strlen(sval);

    if (padding > 0 && !left_align) {
        while (padding--) {
            putchar(' ');
        }
    }

    for ( ; *sval; sval++) {
        putchar(*sval);
    }

    if (padding > 0 && left_align) {
        while (padding--) {
            putchar(' ');
        }
    }
}