#include <ctype.h>
#include <string.h>
#include <stdio.h>

/**
 * Write a program to 'fold' long input lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of
 * input. Make sure your program does something intelligent with very long
 * lines, and if there are no blanks or tabs before the specified column.
 */

#define MAX_LENGTH 1000
#define PAGE_WIDTH 30
#define TAB_SPACES 8

void wrap_line(char line[], int *length, int *position);
void append_char(char line[], int *length, char current_char, int *position);

int main() {
    char current_char;
    char line[MAX_LENGTH];
    int length = 0;
    int position = 1;

    while((current_char = getchar()) != EOF) {
        if (position > PAGE_WIDTH) {
            wrap_line(line, &length, &position);        
        }
        append_char(line, &length, current_char, &position);
    }

    line[length] = '\0';
    printf("%s", line);
}

void wrap_line(char line[], int *length, int *position) {
    // If inside a word, scan back to the beginning
    int word_start = *length - 1;
    while (!isblank(line[word_start]) && !isblank(line[word_start - 1]) && word_start > 0) {
        word_start--;
    }
    // Find the first blank of the string of blanks before that word
    int break_idx = word_start;
    while (isblank(line[break_idx - 1]) && break_idx > 0) {
        break_idx--;
    }

    if (word_start == (*length - 1) && isblank(line[word_start])) {
        // The overflow was caused by whitespace, so replace it with \n
        line[*length - 1] = '\n';
        *position = 1;
    } else if (word_start == 0) {
        // There are no blanks, so force a break
        char temp = line[*length - 1];
        line[*length - 1] = '\n';
        *position = 1;
        line[(*length)++] = temp;
    } else {
        // Capture the word after the break point
        int word_length = *length - word_start;
        char temp[word_length];
        for (int i = 0; i < word_length; i++) {
            temp[i] = line[word_start + i];
        }
        // Update length and insert a newline at the break point
        *length = break_idx;
        line[(*length)++] = '\n';
        *position = 1;
        // Add the captured word back to the line
        for (int i = 0; i < word_length; i++) {
            line[(*length)++] = temp[i];
            (*position)++;
        }
    } 
}

void append_char(char line[], int *length, char current_char, int *position) {
    line[(*length)++] = current_char;
    if (current_char == '\n') {
        *position = 1;
    } else if (current_char == '\t') {
        int spaces = TAB_SPACES - (*position % TAB_SPACES);
        *position += spaces + 1;
    } else {
        (*position)++;
    }
}