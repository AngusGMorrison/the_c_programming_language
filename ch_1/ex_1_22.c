#include <ctype.h>
#include <stdio.h>

/**
 * Write a program to 'fold' long input lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of
 * input. Make sure your program does something intelligent with very long
 * lines, and if there are no blanks or tabs before the specified column.
 * 
 * Note: Unlike other published solutions, this version collects the entire user
 * input into an array and awaits an EOF before printing it. This ensures lines
 * of input and lines of processed text are not mixed together.
 * 
 * Also unlike other solutions, this version trims excess whitespace from
 * the end of each line as it is broken, as specified by the exercise.
 */

#define MAX_LENGTH 1000
#define PAGE_WIDTH 30
#define TAB_SPACES 8

char line[MAX_LENGTH];
int length = 0;
int position = 1;

void wrap_line();
int find_word_start();
int find_break_idx(int word_start);
void break_in_word();
void break_line();
void break_after_word(int word_start, int break_idx);
void append_char(char current_char);

int main() {
    char current_char;

    while((current_char = getchar()) != EOF) {
        if (position > PAGE_WIDTH) {
            wrap_line();        
        }
        append_char(current_char);
    }

    line[length] = '\0';
    printf("%s", line);
}

/* Folds the line by inserting a newline char after the last word before
   PAGE_WIDTH. */
void wrap_line() {
    // If inside a word, scan back to the beginning
    int word_start = find_word_start();
    // Find the first blank of the string of blanks before that word
    int break_idx = find_break_idx(word_start);

    if (word_start == 0) {
        // There are no blanks, so force a break
        break_in_word(); 
    } else if (word_start == (length - 1) && isblank(line[word_start])) {
        /* The overflow was caused by whitespace, so replace it with \n to
           prevent spaces at the start of lines */
        break_line();
    } else {
        // Capture the word after the break point
        break_after_word(word_start, break_idx);
    } 
}

// Scans back through the line to find the start of the current word
int find_word_start() {
    int word_start = length - 1;
    while (!isblank(line[word_start]) && !isblank(line[word_start - 1]) && word_start > 0) {
        word_start--;
    }
    return word_start;
}

// Find the position of the first blank after the last whole word
int find_break_idx(int word_start) {
    int break_idx = word_start;
    while (isblank(line[break_idx - 1]) && break_idx > 0) {
        break_idx--;
    }
    return break_idx;
}

// Break the line mid-word, saving the character that gets replaced by \n
void break_in_word() {
    char temp = line[length - 1];
    break_line();
    line[length++] = temp;
}

// Break the line by adding a line break and resetting position
void break_line() {
    line[length - 1] = '\n';
    position = 1;
}

// Break the line after the last whole word
void break_after_word(int word_start, int break_idx) {
    // Capture the word after the break point
    int word_length = length - word_start;
    char temp[word_length];
    for (int i = 0; i < word_length; i++) {
        temp[i] = line[word_start + i];
    }
    // Update length and insert a newline at the break point
    length = break_idx;
    line[length++] = '\n';
    position = 1;
    // Add the captured word back to the line
    for (int i = 0; i < word_length; i++) {
        line[length++] = temp[i];
        position++;
    }
}

// Adds the current char to the end of the line
void append_char(char current_char) {
    line[length++] = current_char;
    if (current_char == '\n') {
        position = 1;
    } else if (current_char == '\t') {
        int spaces = TAB_SPACES - (position % TAB_SPACES);
        position += spaces + 1;
    } else {
        position++;
    }
}