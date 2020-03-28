/**
 * Modify the sort program to handle an -r flag, which indicates sorting
 * in reverse (decreasing) order. Be sure that -r works with -n.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int max_lines);
int get_line(char *line, int max_len); 
void writelines(char *lineptr[], int nlines, int reverse);
void q_sort(void *lineptr[], int left, int right, int (*comp)(void *, void*));
int numcmp(const char *, const char *);

int main(int argc, char *argv[]) {
    char *flagstr;
    char flag;
    int nlines;
    int numeric = 0;
    int reverse = 0;

    while (argc-- > 1 && (*++argv)[0] == '-') {
        while ((flag = *++argv[0])) {
            switch (flag) {
                case 'n':
                    numeric = 1;
                case 'r':
                    reverse = 1;
                    break;
                default:
                    printf("Unknown flag: %c\n", flag);
            }                  
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        q_sort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) (numeric ? numcmp : strcmp));
        writelines(lineptr, nlines, reverse);
        return 0;
    } else {
        printf("Input too big to sort\n");
        return 1;
    }
}

// #include <stdlib.h>

#define MAXLEN 1000

int readlines(char *lineptr[], int max) {    
    char line[MAXLEN];
    char *saved_line;
    int len;
    int nlines = 0;
    
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= max || (saved_line = malloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';   // Remove newline
            strcpy(saved_line, line);
            lineptr[nlines++] = saved_line;
        }
    }

    return nlines;
}

int get_line(char *line, int max_len) {
    int current;
    int len = 0;

    while ((current = getchar()) != EOF && current != '\n')
        line[len++] = current;
    
    if (current == '\n') 
        line[len++] = current;
    
    line[len] = '\0';
    return len;
}

void q_sort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int first, int second);

    if (left >= right)
        return;
    
    // Swap the value on the left-hand side with the value in the middle
    swap(v, left, (left + right) / 2);
    // Last = the value on the left-hand side (the value that was in previously in the middle)
    last = left;
    // i is the value after last. Up to and including the right-hand side, do...
    for (i = left + 1; i <= right; i++) {
        // If the value at i is less than the first value in the array...
        if ((*comp)(v[i], v[left]) < 0) {
            // Swap the value following the last value to be swapped with i
            // If i == 1, it will stay in the same place
            swap(v, ++last, i);
        } 
    }
    // Swap the value on the left with the last value to be swapped.
    // This makes everything on the left of left smaller than left
    swap(v, left, last);
    // Split the array in half and quicksort again
    q_sort(v, left, last - 1, comp);
    q_sort(v, last + 1, right, comp);
}

void swap(void *v[], int first, int second) {
    void *temp = v[first];
    v[first] = v[second];
    v[second] = temp;
}

#include <stdlib.h>

int numcmp(const char *s1, const char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 - v2 < 0)
        return -1;
    else if (v1 - v2 > 0)
        return 1;
    else
        return 0;
}

void writelines(char *lineptr[], int nlines, int reverse) {
    if (reverse) {
        for (int i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    } else {
        for (int i = 0; i < nlines; i++) 
            printf("%s\n", lineptr[i]);
    }
}