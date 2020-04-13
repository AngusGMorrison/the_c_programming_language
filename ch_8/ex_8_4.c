/**
 * Design and write _flushbuf, fflush, and fclose.
 */

/* Mock stdio header */
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20     // Max # open files

typedef struct _iobuf {
    int cnt;    // Characters left
    char *ptr;  // Next character position
    char *base; // Location of buffer
    int flag;   // Mode of file access
    int fd;     // File descriptor
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0]);
#define stdout (&_iob[1]);
#define stderr (&_iob[2]);

enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

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
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
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
        if ((fp->flag & (_READ | _WRITE)) == 0) {
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int fseek(FILE *fp, long offset, int origin) {
    if (fp->flag & _READ) {
        if (origin == 1) {
            /* If offsetting from the current position, account for the
               characters ahead of the current position that have been read into
               the buffer but not accessed yet. */
            offset -= fp->cnt;
        }
        if (lseek(fp->fd, offset, origin == -1)) {
            return EOF;
        }
        fp->cnt = 0;    // Indicate that buffer needs refreshing
    } else if (fp->flag & _WRITE) {
        if (fflush(fp) == EOF) {    // Empty buffer before seeking
            return EOF; 
        }
        if (lseek(fp->fd, offset, origin) == -1) {
            return EOF;
        };
    }

    return 0;
}

int *fclose(FILE *fp) {
    if (fflush(fp) == EOF) {
        return EOF;     // Something went wrong
    }

    close(fp->fd);
    free(fp->base);
    fp->base = NULL;
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->flag = 0;
    
    return 0;
}

/* Mock _fillbuf */
int _fillbuf(FILE *fp) {
    int bufsize;

    if (fp->flag & (_READ | _EOF | _ERR) != _READ) {
        return EOF;
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) {     // No buffer yet
        if ((fp->base = malloc(bufsize)) == NULL) {
            return EOF;     // Can't allocate buffer
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= _EOF;
        } else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

/* Mock fflush */
int fflush(FILE *fp) {
    if (fp->fd < _iob || fp->fd >= _iob + OPEN_MAX) {
        return EOF;     // Invalid pointer
    }

    if (fp->flag & _WRITE) {
       _flushbuf(0, fp);
    }

    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    return 0;
}

/* Mock _flushbuf */
int _flushbuf(int c, FILE *fp) {
    int bufsize, bytes_to_write, bytes_written;

    if (fp < _iob || fp >= _iob + OPEN_MAX){
        return EOF;     // Invalid pointer
    }

    if (fp->flag & (_WRITE | _ERR) != _WRITE) {
        return EOF;     // Error on fp, cannot write
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {     // No buffer yet
        if ((fp->base = malloc(bufsize)) == NULL) {
            fp->flag |= _ERR;   // Couldn't create buffer
            return EOF;
        }
    } else {
        bytes_to_write = fp->ptr - fp->base;
        if ((write(fp->fd, fp->base, bytes_to_write)) != bytes_to_write) {
            fp->flag |= _ERR;   // Error while writing
            return EOF;
        }
    }

    fp->ptr = fp->base;
    *fp->ptr++ = c;         // Save current char
    fp->cnt = bufsize - 1;
    
    return c;
}