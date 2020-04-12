/**
 * cat: concatenate files, version 2 (copied for practice).
 */ 

#include <stdio.h>

main(int argc, char *argv[]) {
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