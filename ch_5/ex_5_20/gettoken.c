/**
 * gettoken: return next token.
 */ 

#include <ctype.h>
#include <string.h>
#include "headers.h"

extern int tokentype;
extern char token[];
extern int prevtoken;

int gettoken(void) {
    int c;
    char *p = token;

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
        *p = '\0';
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