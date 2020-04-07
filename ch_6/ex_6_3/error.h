#ifndef ERROR_H
#define ERROR_H

void arg_error(char *message);
void invalid_file_error(char *message, char *filename);
void null_pointer_error(char *pointer_name, char *func_name);
void buffer_overflow_error(char c);

#endif