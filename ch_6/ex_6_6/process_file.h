#ifndef PROCESS_FILE_H
#define PROCESS_FILE_H

#include <stdio.h>

void process_file();
int get_next_token(char *token);
static char get_char();
static void unget_char(char c);
static char *str_dup(char *str);

#endif