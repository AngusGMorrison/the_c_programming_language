#ifndef READ_VARIABLES_H
#define READ_VARIABLES_H

int get_variable(char *variable);
static int get_word(char *word, int limit);
static int getch();
static void ungetch(int c);
static int binsearch(char *key, const char *table[], int nkeys);

#endif