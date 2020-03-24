/** Rewrite readlines to store lines in an array supplied by main, rather than
 * calling alloc to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   // Max lines to be sorted
#define MAXLEN 1000     // Max length of any input line


char *lineptr[MAXLINES]; // Pointers to text lines

int readlines(char *lineptr[], int maxlines, char *lines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

// Sort input lines
int main() {
    int nlines;                      //Number of input lines read
    char line_store[MAXLINES * MAXLEN];   // Array able to hold all possible lines at max length

    if ((nlines = readlines(lineptr, MAXLINES, line_store)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

int get_line(char *s, int lim);
char *alloc(int);

// readlines: read input lines
int readlines(char *lineptr[], int maxlines, char *line_store) {
    int len, nlines, pos;
    char line[MAXLEN];

    nlines = 0;
    int total_len = 0;  // Tracks total length of line_store
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (total_len += len) > MAXLEN * MAXLINES)
            // Number of lines or line store capacity exceeded
            return -1;
        else {
            line[len - 1] = '\0';   //Delete newline
            strcpy(line_store, line);   // Copy current line onto end of line_store
            lineptr[nlines++] = line_store;     // Set the line pointer to the beginning of the current line in line_store
            line_store += len;  // Move the position of line_store to the end of the line that was just added
        }
    return nlines;
}

int get_line(char *s, int lim) {
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != '\n' && i < lim - 1; i++)
        *s++ = c;
    
    if (c == '\n') {
        *s++ = c;
        i++;
    }
    
    *s = '\0';
    return i;
}

// qsort: sort v[left]...v[right] into increasing order
void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *i[], char *j[]);

    if (left >= right)
        return;
    
    swap(&v[left], &v[(left + right) / 2]);

    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(&v[++last], &v[i]);
    swap(&v[left], &v[last]);

    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *i[], char *j[]) {
    char *temp = *i;
    *i = *j;
    *j = temp;
}

// writelines: write output lines
void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}