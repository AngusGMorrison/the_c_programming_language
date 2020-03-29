/**
 * Make dcl recover from input errors.
 * 
 * Solution: by changing dcl and dirdcl to recursively return negative error
 * codes from anywhere in the stack back to main, we make it so that when
 * something goes wrong a single error message is printed, the program does
 * not attempt to parse and display the reset of the syntactically invalid
 * code, and it awaits fresh input that isn't corrupted by previous incorrect
 * input.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int dcl(void);
int dirdcl(void);

int tokentype;              // Type of last token
char token[MAXTOKEN];       // Last token string
char name[MAXTOKEN];        // Identifier name
char datatype[MAXTOKEN];    // Data type = char, int, etc.
char out[1000];             // Output string

// Convert declaration to words
int main(void) {
    while (gettoken() != EOF) {
        strcpy(datatype, token);    // 1st token on line is the datatype
        out[0] = '\0';
        if (dcl() == 0) {      // Parse the rest of the line
            if (tokentype != '\n')
                printf("Syntax error\n");
            else
                printf("%s: %s %s\n", name, out, datatype);
        }
    }
}

// Return next token
int gettoken(void) {
    int getch(void);
    void ungetch(int c);

    int c;
    char *p = token;

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

#define MAXBUF 10
int buf[MAXBUF];
int bufpos = 0;

int getch(void) {
    return bufpos ? buf[--bufpos] : getchar();
}

void ungetch(int c) {
    if (bufpos < MAXBUF - 1) {
        buf[bufpos++] = c;
    } else {
        printf("Error: buffer full\n");
    }
}

// Parse a declarator
int dcl(void) {
    int stars;
    for (stars = 0; gettoken() == '*'; )
        stars++;

    if (dirdcl() == -1)
        return -1;

    while (stars-- > 0)
        strcat(out, " pointer to");

    return 0;
}

// Lore: Parse a direct declarator
int dirdcl(void) {
    int type;

    if (tokentype == '(') {     // (dcl)
        if (dcl() == -1)
            return -1;

        if (tokentype != ')') {
            printf("Error: missing )\n");
            return -1;
        }      
    } else if (tokentype == NAME)       // Variable name
        strcpy(name, token);
    else {
        printf("Error: expected name or (dcl)\n");
        return -1;
    }
         
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }

    return 0;
}