#ifndef ERROR_H
#define ERROR_H

void argc_error();
void fopen_error(char *path);
void buffer_overflow_error(char overflow);
void null_pointer_error(char *p_name, char *func_name);

#endif