#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[]);
void copy(char to[], char from[]);

int main() {
    int current_len, max_len = 0;
    char current_line[MAXLINE], longest_line[MAXLINE];

    /* Get each line, comparing its length to the current max length and
       replacing longest_line if the new one is longer. */
    while ((current_len = get_line(current_line)) > 0) {
        if (current_len > max_len) {
            max_len = current_len;
            copy(longest_line, current_line);
        }
    }
    // If there was any line at all...
    if (max_len > 0) {
        printf("Line of length %i: %s\n", max_len, longest_line);
    }
    return 0;
}

// Read a line into line[] and return its length
int get_line(char line[]) {
    int current_char, length = 0;
    
    /* Until the end of the input line is reached, increment the length counter,
       only adding the character to the line array if length is smaller than
       MAXLINE - 1. */
    while ((current_char = getchar()) != EOF && current_char != '\n') {
        if (length < MAXLINE - 1) {
            line[length] = current_char;
        }
        ++length;
    }

    /* If the final character was newline, not EOF, add the newline character
       to the array and increment the line length. */
    if (current_char == '\n') {
        line[length] = current_char;
        ++length;
    }
    // Terminate the string, but don't count the null char in the line length
    line[length] = '\0';
    return length;
}

// Copy 'from' into 'to'; assume 'to' is big enough
void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}