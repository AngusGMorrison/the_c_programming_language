/**
 * Modify undcl so that it does not add redundant parentheses to declarations.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int peekahead(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(void) {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if ((type = peekahead()) == PARENS || type == BRACKETS)
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("Invalid input at %s\n", token);
        }
        printf("%s\n", out);
    }
    return 0;
}

int prevtoken = 0;

// Gets the next token and sets a flag for it to be pushed back
int peekahead(void) {
    int type = gettoken();
    prevtoken = 1;
    return type;
}

int gettoken(void) {
    int getch(void);
    void ungetch(int c);

    int c;
    char *p = token;

    // Return the previous token if flagged by peekahead()
    if (prevtoken) {
        prevtoken = 0;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p ='\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

#define MAXBUF 10
static int buf[MAXBUF];
static int bufpos = 0;

int getch(void) {
    return bufpos > 0 ? buf[--bufpos] : getchar(); 
}

void ungetch(int c) {
    if (bufpos < MAXBUF - 1) {
        buf[bufpos++] = c;
    } else {
        printf("Error: buffer full\n");
    }
}
