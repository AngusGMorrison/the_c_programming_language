/**
 * Expand dcl to handle declarations with function argument types, qualifiers
 * like const, and so on.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"

void dirdcl(void);
void errmsg(char *);

extern int tokentype;       // Type of last token
extern char token[];        // Last token string
extern char name[];         // Identifier name
extern char datatype[];     // char, int, etc.
extern int prevtoken;       // Flags whether to reuse last token
extern char out[];

// Convert declaration to words
int main(void) {
    prevtoken = 0;
    while (gettoken() != EOF) {
        strcpy(datatype, token);    // 1st token is always the datatype
        out[0] = '\0';
        dcl();      // Parse the rest of the line
        if (tokentype != '\n')
            printf("Syntax error\n");
        printf("%s:%s %s\n", name, out, datatype);
    }
    return 0;
}

// Parse a declarator
void dcl(void) {
    int stars;

    for (stars = 0; gettoken() == '*'; )
        stars++;
    dirdcl();
    while (stars-- > 0)
        strcat(out, " pointer to");
}

// Parse a direct declaration
void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        // Parentheses must surround a declarator, so parse it
        dcl();
        if (tokentype != ')')
            errmsg("Error: missing )\n");
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else
        prevtoken = 1;

    while (
        (type = gettoken()) == PARENS ||
        type == BRACKETS ||
        type == '('
    ) {
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function expecting");
            paramdcl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

// Print error message and indicate previous token is available
void errmsg(char *msg) {
    printf("%s", msg);
    prevtoken = 1;
}






