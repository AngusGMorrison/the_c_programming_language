/**
 * Our version of getword does not properly handle underscores, string
 * constants, comments, or preprocessor control lines. Write a better version.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct key {
    char *word;
    int count;
} keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    { "define", 0 },
    { "do", 0 },
    { "double", 0 },
    { "else", 0 },
    { "enum", 0 },
    { "extern", 0 },
    { "float", 0 },
    { "for", 0 },
    { "goto", 0 },
    { "if", 0 },
    { "int", 0 },
    { "long", 0 },
    { "register", 0 },
    { "return", 0 },
    { "short", 0 },
    { "signed", 0 },
    { "sizeof", 0 },
    { "static", 0 },
    { "struct", 0 },
    { "switch", 0 },
    { "typedef", 0 },
    { "union", 0 },
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 }			
};

#define NKEYS sizeof(keytab) / sizeof(keytab[0])
#define MAXWORD 100

int getword(char *word, int lim);
int getch();
void ungetch(int c);
int binsearch(char *word, struct key *tab, int n);

// Count C keywords
int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    }
    return 0;
}

// Get next word or character from input
int getword(char *word, int lim) {
    int c, next, getch(void);
    void ungetch(int c);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '#' && c != '"' && c != '/') {
        *w = '\0';
        return c;
    }

    if (c == '#' || c == '"' || c == '/') {
        if (c == '#' && !isalpha(next = getch())) {
            ungetch(next);
            *w = '\0';
            return c;
        } else if (c == '"' && !isalnum(next = getch())) {
            ungetch(next);
            *w = '\0';
            return c;
        } else if (c == '/') {
            if ((next = getch()) == '*') {
                while (isblank(next = getch()))
                    ;
                *--w = next;
                w++;
            } else {
                ungetch(next);
                *w = '\0';
                return c;
            } 
        } else {
            *--w = next;
            w++;
        }
    }

    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define MAXBUF 10
static int buf[MAXBUF];
static int bufpos = 0;

int getch() {
    return bufpos > 0 ? buf[--bufpos] : getchar();
}

void ungetch(int c) {
    if (bufpos < MAXBUF - 1) {
        buf[bufpos++] = c;
    } else {
        printf("Error: buffer full\n");
    }
}

// Find word in tab[0]..tab[n-1]
int binsearch(char *word, struct key *tab, int n) {
    int cond;
    int low, mid, high;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
