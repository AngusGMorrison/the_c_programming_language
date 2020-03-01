#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

void reverse(char string[]);
void swap(char *first, char *second);

int main() {
    char current_char;
    char current_line[MAX_LENGTH];
    int length = 0;

    while ((current_char = getchar()) != EOF) {
        if (current_char == '\n') {
            // When a newline is reached, terminate the string and reverse it
            current_line[length++] = '\n';
            current_line[length] = '\0';
            reverse(current_line);
            printf("%s\n", current_line);
            length = 0;     // Reset length for the next loop
        } else {
            // Add each character to the array until a newline is reached
            current_line[length++] = current_char;
        }
    }
}

void reverse(char string[]) {
    /* Starting from the left and right sides of the array, swap each pair until
       the indexes meet. */
    for (int left = 0, right = strlen(string) - 1; left < right; left++, right--) {
        swap(&string[left], &string[right]);
    }
}

void swap(char *first, char *second) {
    /* Swap the value at the address of the first character with the value at
       the address of the second. */
    char temp = *first;
    *first = *second;
    *second = temp;
}
