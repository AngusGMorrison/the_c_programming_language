#include <ctype.h>
#include <stdio.h>

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

void wrap_line() {
    int word_start = find_word_start();
    int break_idx = find_break_idx(word_start);

    if (word_start == 0) {
        break_in_word(); 
    } else if (word_start == (length - 1) && isblank(line[word_start])) {
        break_line();
    } else {
        break_after_word(word_start, break_idx);
    } 
}

int find_word_start() {
    int word_start = length - 1;
    while (!isblank(line[word_start]) && !isblank(line[word_start - 1]) && word_start > 0) {
        word_start--;
    }
    return word_start;
}

int find_break_idx(int word_start) {
    int break_idx = word_start;
    while (isblank(line[break_idx - 1]) && break_idx > 0) {
        break_idx--;
    }
    return break_idx;
}

void break_in_word() {
    char temp = line[length - 1];
    break_line();
    line[length++] = temp;
}

void break_line() {
    line[length - 1] = '\n';
    position = 1;
}

void break_after_word(int word_start, int break_idx) {
    int word_length = length - word_start;
    char temp[word_length];
    for (int i = 0; i < word_length; i++) {
        temp[i] = line[word_start + i];
    }
    length = break_idx;
    line[length++] = '\n';
    position = 1;
    for (int i = 0; i < word_length; i++) {
        line[length++] = temp[i];
        position++;
    }
}

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