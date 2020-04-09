/**
 * Implement a simple version of the #define processor (i.e., no arguments)
 * suitable for use with C programs, based on the routines of this section. You
 * may also find getch and ungetch helpful.
 */

#include <stdio.h>
#include "error.h"
#include "process_file.h"

extern FILE *in, *out;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        argc_error();
    }

    if ((in = fopen(argv[1], "r")) == NULL) {
        fopen_error(argv[1]);
    }

    char *out_path = "./out.c";
    if ((out = fopen(out_path, "w")) == NULL) {
        fclose(in);
        fopen_error(out_path);
    }

    process_file(in, out);
    return 0;
}