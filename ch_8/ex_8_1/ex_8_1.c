/**
 * Rewrite the program cat from Chapter 7 using read, write, open and close
 * instead of their standard library equivalents. Perform experiements to
 * determine the relevant speeds of the two versions.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Provides access to the POSIX OS API

float get_secs(int start, int end);
int posix_cat(int argc, char *argv[]);
int posix_copy(int descriptor, char *buf, int n_bytes);
int stdlib_cat(int argc, char *argv[]);
void stdlib_copy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[]) {
    int start, end;
    float posix_secs, stdlib_secs;

    // Time POSIX call version of cat
    start = clock();
    for (int i = 0; i < 1000; i++) {
        posix_cat(argc, argv);
    }
    end = clock();
    posix_secs = get_secs(start, end);

    // Time stdlib version of cat
    start = clock();
    for (int i = 0; i < 1000; i++) {
        stdlib_cat(argc, argv);
    }
    end = clock();
    stdlib_secs = get_secs(start, end);

    printf("POSIX version: %f secs\n", posix_secs);
    printf("stdlib version: %f secs\n", stdlib_secs);
}

float get_secs(int start, int end) {
    return ((float) end - start) / CLOCKS_PER_SEC;
}

#define BUF_SIZE 1000

// Concatenate files using calls to the POSIX API
int posix_cat(int argc, char *argv[]) {
    char buf[BUF_SIZE];
    int read_descriptor, n_bytes;

    if (argc == 1) {
        read_descriptor = 0;    // Read from stdin
        posix_copy(read_descriptor, buf, BUF_SIZE);
    } else {
        while (--argc > 0) {
            read_descriptor = open(*++argv, O_RDONLY, 0);
            if (read_descriptor == -1) {
                char *err_msg = "Error opening file ";
                write(2, err_msg, sizeof(err_msg));
                write(2, *argv, sizeof(*argv));
                write(2, "\n", 2);
                exit(1);
            } else {
                posix_copy(read_descriptor, buf, BUF_SIZE);
                close(read_descriptor);
            }
        }
    }

    return 0;
}

int posix_copy(int descriptor, char *buf, int n_bytes) {
    int bytes_read;
    
    while ((bytes_read = read(descriptor, buf, BUF_SIZE)) > 0) {
        if (write(1, buf, bytes_read) == -1) {
            char *err_msg = "Error writing to stdout\n";
            write(2, err_msg, sizeof(err_msg));
            exit(2);
        };
    }

    return 0;
}

// Concatenate files using standard library methods
int stdlib_cat(int argc, char *argv[]) {
    FILE *fp;
    void stdlib_copy(FILE *in, FILE *out);
    char *prog = argv[0];   // Program name for errors

    if (argc == 1) {    // No args; copy standard input
        stdlib_copy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                stdlib_copy(fp, stdout);
                fclose(fp);
            }
        }
    }

    // ferror returns non-zero if an error occured on the stream
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }

    return 0;
}

// Copy file ifp to file ofp
void stdlib_copy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}