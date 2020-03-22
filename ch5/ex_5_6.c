/**
 * Rewrite appropriate programs from earlier chapters and excercises with
 * pointers instead of array indexing. Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3 and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>

void get_line(char *line);
int atoi(char *a);
void reverse(char *s);

#define MAXLEN 1000

int main() {
    // Test get_line
    // char line[MAXLEN];
    // get_line(line);
    // printf("%s\n", line);

    // Test atoi
    // printf("%i\n", atoi("123"));

    // Test reverse
    char s[] = "Hello, World.";
    reverse(s);
    printf("%s\n", s);
}

void get_line(char *line) {
    char *line_start = line;
    while ((*line = getchar()) != EOF && *line != '\n')
        line++;

    if (*line == EOF)
        *line = '\n';
        
    *++line = '\0';
}

int atoi(char *a) {
    int sign = *a == '-' ? -1 : 1;
    if (*a == '-' || *a == '+')
        a++;
    
    int number = 0;
    while (*a) {
        number = number * 10 + (*a - '0');
        a++;
    }

    return number * sign;
}

void reverse(char *s) {
    char *end = s;
    while (*(end + 1))
        end++;

    for (; s < end; s++, end--) {
        char temp = *end;
        *end = *s;
        *s = temp;
    }
}