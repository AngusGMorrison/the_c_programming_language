#ifndef READ_DOCUMENT_H
#define READ_DOCUMENT_H

#include "node.h"

node *read_document();
static char *get_word();
static char *duplicate(char *word);
static char getch();
static void ungetch(char c);
int is_noise_word(char *word);

#endif