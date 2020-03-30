#ifndef HEADERFILE_H
#define HEADERFILE_H

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

// main.c
void dcl(void);
void errmsg(char *);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
int prevtoken;
char out[1000];

// getch.c
int getch(void);
void ungetch(int c);

// gettoken.c
int gettoken(void);

// paramdcl.c
void paramdcl(void);

#endif