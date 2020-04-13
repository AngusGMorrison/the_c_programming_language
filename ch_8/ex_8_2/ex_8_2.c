/**
 * Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 * 
 * Note: Using bit fields, the code is larger and execution slower. Bit fields
 * are also machine-dependent.
 */

/* Mock stdio header */
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20     // Max # open files

struct _flags {
    unsigned int is_read : 1;
    unsigned int is_write : 1;
    unsigned int is_unbuf : 1;
    unsigned int is_eof : 1;
    unsigned int is_err : 1;
};

typedef struct _iobuf {
    int cnt;    // Characters left
    char *ptr;  // Next character position
    char *base; // Location of buffer
    struct _flags flags;   // Mode of file access
    int fd;     // File descriptor
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0]);
#define stdout (&_iob[1]);
#define stderr (&_iob[2]);

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p->flag & _ERR) != 0))
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin);
#define putchar(x)  putc((x), stdout);


/* Initialize _iob with stdin, stdout and stderr for current program. */
FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, { 1, 0, 0, 0, 0 }, 0 },
    { 0, (char *) 0, (char *) 0, { 0, 1, 0, 0, 0 }, 1 },
    { 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0 }, 2 }
};

/* Mock fopen */
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666  // RW for owner, group, others

FILE *fopen(char *name, char *mode) {
    int descriptor;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (!fp->flags.is_read && !fp->flags.is_write) {
            break;  // Found free slot
        }
    }
    if (fp >= _iob + OPEN_MAX) {
        return NULL;    // No free slots
    }

    if (*mode == 'w') {
        descriptor = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((descriptor = open(name, O_WRONLY, 0)) == -1) {
            descriptor = creat(name, PERMS);
        }
        lseek(descriptor, 0L, 2);
    } else {
        descriptor = open(name, O_RDONLY, 0);
    }
    if (descriptor == -1) {
        return NULL;    // Couldn't access name
    }

    fp->fd = descriptor;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flags.is_read = 1;
        fp->flags.is_write = 0;
    } else {
        fp->flags.is_read = 0;
        fp->flags.is_write = 1;
    }
    fp->flags.is_unbuf = 0;
    fp->flags.is_eof = 0;
    fp->flags.is_err = 0;
    return fp;
}

/* Mock _fillbuf */
int _fillbuf(FILE *fp) {
    int bufsize;

    if (!fp->flags.is_read || fp->flags.is_eof || fp->flags.is_err) {
        return EOF;
    }

    bufsize = (fp->flags.is_unbuf) ? 1 : BUFSIZ;

    if (fp->base == NULL) {     // No buffer yet
        if ((fp->base = malloc(bufsize)) == NULL) {
            return EOF;     // Can't allocate buffer
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flags.is_eof = 1;
        } else {
            fp->flags.is_err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}