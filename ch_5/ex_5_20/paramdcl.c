/**
 * paramdcl: parse a parameter declaractor.
 */ 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

void dclspec(void);
int typespec(void);
int typequal(void);
int compare(char **, char **);

extern int tokentype;
extern char token[];
extern int prevtoken;
extern char out[];

void paramdcl(void) {
    do {
        dclspec();
    } while (tokentype == ',');

    if (tokentype != ')')
        errmsg("error: missing ) in parameter declaration\n");
}

// Declaration specification
void dclspec(void) {
    char temp[MAXTOKEN];
    
    temp[0] = '\0';
    gettoken();

    do {
        if (tokentype != NAME) {
            prevtoken = 1;
            dcl();
        } else if (typespec()) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else if (typequal()) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            errmsg("Error: unknown type in parameter list\n");
            exit(1);
        }
    } while (tokentype != ',' && tokentype != ')');

    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

// Return true if token is a type specifier
int typespec(void) {
    char *types[] = {
        "char",
        "double",
        "float",
        "int",
        "long",
        "short",
        "void"
    };
    printf("%s\n", token);
    char *pt = token;

    if (bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char *),
        compare) == NULL)
        return 0;
    else
        return 1;
}

// Return true if token is a type-qualifier
int typequal(void) {
    char *typeqs[] = {
        "const",
        "volatile"
    };
    char *pt = token;

    if (bsearch(&pt, typeqs, sizeof(typeqs) / sizeof(char *), sizeof(char *),
        compare) == NULL)
        return 0;
    else
        return 1;   
}

int compare(char **s, char **t) {
    return strcmp(*s, *t);
}