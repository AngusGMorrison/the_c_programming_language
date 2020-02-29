#include <ctype.h>
#include <stdio.h>

/**
 * Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 * 
 * Note: this implementation allows for duplicate words in both horizontal and
 * vertical histograms.
 * 
 * To remain simple for beginners to follow, this approach does not use pointers
 * to break vertical_histogram into smaller functions.
 */

#define MAX_LENGTH 100
#define MAX_WORDS 8
#define COLUMN_FORMAT "%-20s"

void horizontal_histogram();
void vertical_histogram();

int main() {
    // Test functions one at a time by commenting out the other
    // horizontal_histogram();
    vertical_histogram();
}

void horizontal_histogram() {
    int length = 0;
    char current_char;
    char current_word[MAX_LENGTH];

    printf("Enter text: ");
    while ((current_char = getchar()) != EOF) {
        // At the end of each non-empty word, print its histogram row
        if (length > 0 && (isblank(current_char) || current_char == '\n')) {
            // Terminate the string
            current_word[length] = '\0';
            // Print the word, followed by its length in hashes
            printf("%-20s | ", current_word);
            for (int i = 0; i < length ; i++) {
                putchar('#');
            }
            putchar('\n');
            // Reset the length counter in preparation for the next word
            length = 0;
        } else {
            current_word[length] = current_char;
            length++;
        }
    }
}

void vertical_histogram() {
    /* Keep a record of all words and their lengths.
       Limited to 8 words to fit them all in the terminal. */
    char words[MAX_WORDS][MAX_LENGTH];
    int word_lengths[MAX_LENGTH];
    int word_count = 0;
    // Track each word as it is input
    char current_char;
    int current_word_length = 0;
    int max_word_length = 0;

    printf("Enter text: ");
    while ((current_char = getchar()) != EOF && word_count < MAX_LENGTH) {
        // When a word ends...
        if (current_word_length > 0 && (
            isblank(current_char) || ispunct(current_char) || current_char == '\n')) {
            /* Add the terminating character, add the word to the words array,
               and increment the total number of words. */
            words[word_count][current_word_length] = '\0';
            word_lengths[word_count] = current_word_length;
            word_count++;
            /* Keep a record of the greatest word length. This will be the
               maximum column height for the histogram. */
            if (current_word_length > max_word_length) {
                max_word_length = current_word_length;
            }
            current_word_length = 0;
        } else {
        /* If the word hasn't ended, keep adding its characters into the
           current position in the array. */
            words[word_count][current_word_length] = current_char;
            current_word_length++;
        }
    }

    // Until the maximum possible word length has been reached...
    for (int i = max_word_length; i > 0; i--) {
        // Iterate through every word...
        for (int j = 0; j < word_count; j++) {
            // If the word's length is at least as much as the current length, i...
            if (word_lengths[j] >= i) {
                // Print a hash in that word's column
                printf(COLUMN_FORMAT, "#");
            } else {
                // Or add the correct horizontal spacing if not
                printf(COLUMN_FORMAT, "");
            }
        }
        putchar('\n');
    }

    // Print each word as a column heading
    for (int i = 0; i < word_count; i++) {
        printf(COLUMN_FORMAT, words[i]);
    }
    putchar('\n');
}