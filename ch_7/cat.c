/**
 * cat: concatenate files, version 2 (copied for practice).
 */ 

#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *in, FILE *out);
    char *prog = argv[0];   // Program name for errors

    if (argc == 1) {    // No args; copy standard input
        filecopy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }

    // ferror returns non-zero if an error occured on the stream
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }

    exit(0);
}

// Copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}