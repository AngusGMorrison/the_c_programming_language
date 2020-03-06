#include <stdio.h>
#include <string.h>

/**
 * Write a progam entab that replaces strings of blanks with a minimum number of
 * tabs and blanks to achieve the same spacing. Use the same tab stops as for
 * detab. When either a tab or a single blank would suffice to reach a tab stop,
 * which should be given preference?
 * 
 * Note: the tricky thing here is that tabs represent a different number of
 * spaces depending on your current position within a tab column. If you're 4
 * characters in to an 8-space tab column and you press tab, the tab will render
 * 4 spaces wide. If you're 7 characters in, the tab will be only 1 space wide.
 * 
 * The solution is to use two types of length counter: 'length' tracks the
 * number of ASCII characters in the string. '\t' and ' ' both count
 * as 1. 'position' counts the actual keypresses, ignoring conversions
 * between blanks and tabs. This represents how the line will be rendered and
 * tells you how close you are to the next tab stop.
 */

#define MAX_LINE 1000
/* To render correctly, TAB_SPACES must match your terminal's tab width
   setting. */
#define TAB_SPACES 8

void print_line(char line[]);

int main() {
    char current_char;
    char line[MAX_LINE];
    int length = 0;     // Tracks array length in actual chars
    int position = 1;   /* Tracks line 'position' into which current_char is
                           being inserted. Counts every keypress, even if
                           multiple blanks are converted to a single tab. */  
    int blanks = 0;
    int tabs = 0;

    while((current_char = getchar()) != EOF && current_char != '\n') {
        if (current_char == ' ') {
            if (position % TAB_SPACES == 0) {
                /* If the position of the line means the current blank has
                   reached a tab stop, replace all pending blanks with a tab. */
                tabs++;
                blanks = 0;
            } else {
                /* If position is not a tab stop, count it as a blank. */
                blanks++;
            }
        } else {
            /* When a non-blank is reached, insert all the tabs and blanks, tabs
               first. Use length, not position, to reflect the actual characters
               being inserted into the array. */
            for ( ; tabs > 0; --tabs) {
                line[length++] = '\t';
            }
            for ( ; blanks > 0; --blanks) {
                line[length++] = ' ';
            }
            // After all tabs and blanks, insert the non-blank char.
            line[length++] = current_char;
        }
        // Increment position with every character entered.
        position++;
    }

    if (current_char == '\n') {
        line[length++] = '\n';
    }

    line[length] = '\0';
    print_line(line);
}

/* Print, replacing tabs and blanks with visible characters to verify the
   solution (optional visualisation). */
void print_line(char line[]) {
    int length = strlen(line);
    // for (int i = 0; i < length; i++) {
    //     if (line[i] == '\t') {
    //         line[i] = '^';
    //     } else if (line[i] == ' ') {
    //         line[i] = '_';
    //     }
    // }
    printf("%s\n", line);
}