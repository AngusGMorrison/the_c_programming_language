/**
 * Modify the fsize program to print the other information contained in the
 * inode entry.
 */

/* dirent.h contains the max length of a filename, the Dirent struct (which
   holds an inode number and name for a file), the DIR struct (which contains
   a file descriptor for the enclosing directory and a Dirent of child file),
   and methods such as opendir, readdir, and closedir. */
#include <dirent.h>
/* sys/stat.h describes the structure returned by the system call "stat" on a
   file, along with the flags it uses. The types used by struct stat are defined
   by sys/types.h. */
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void fsize(char *);

int main(int argc, char **argv) {
    if (argc == 1) {    // Default to the current directory
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }

    return 0;
}

void dirwalk(char *, void (*fcn)(char *));
void print_stats(char *name, struct stat stbuf);
void print_time(char *stat, time_t time);

// Print size of file "name"
void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }

    print_stats(name, stbuf);
}

void print_stats(char *name, struct stat stbuf) {
    printf("%8lld %s\n", stbuf.st_size, name);
    printf("st_dev: %i\n", stbuf.st_dev);
    printf("st_ino: %llu\n", stbuf.st_ino);
    printf("st_mode: 0%o\n", stbuf.st_mode);
    printf("st_nlink: %i\n", stbuf.st_nlink);
    printf("st_uid: %i\n", stbuf.st_uid);
    printf("st_gid: %i\n", stbuf.st_gid);
    printf("st_rdev: %i\n", stbuf.st_rdev);
    print_time("st_atime", stbuf.st_atime);
    print_time("st_mtime", stbuf.st_mtime);
    print_time("st_ctime", stbuf.st_ctime);
    printf("\n");
}

void print_time(char *stat, time_t time) {
    char buf[26];
    struct tm *local;

    local = localtime(&time);
    strftime(buf, 26, "%Y-%m-%d %H:%M:%S", local);
    printf("%s: %s\n", stat, buf);
}

#define MAX_PATH 1024

// Apply fcn to all files in dir
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;    // Skip self and parent
        }

        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
        } else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }

    closedir(dfd);
}