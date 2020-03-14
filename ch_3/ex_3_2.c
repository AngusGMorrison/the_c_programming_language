#include <stdio.h>
#include <string.h>

/**
 * Write a function escape(s, t) that converts characters like newline and tab
 * into visible escape sequences like \n and \t as it copies the string t to s.
 * Use a switch. Write a function for the other direction as well, converting
 * escape sequences into the real characters.
 */

void escape(char *s, char *t);
void imprison(char *t, char *s);

int main() {
    char s[] = "Hey there!\tThis is a test string.\nIt has newlines and tabs.";

    int len = strlen(s);
    // Must be at least twice the size of s to account for all-escape strings
    char t[len * 2 + 1];
    escape(s, t);
    printf("%s\n", t);

    imprison(t, s);
    printf("%s\n", s);
}

void escape(char *s, char *t) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++, j++) {
        switch (s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j] = 't';
                break;
            default:
                t[j] = s[i];
        }  
    }
    t[j] = '\0';
}

void imprison(char *t, char *s) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; i++, j++) {
        switch (t[i]) {
            case '\\':
                if (t[i + 1] == 'n') {
                    s[j] = '\n';
                    i++;
                } else if (t[i + 1] == 't') {
                    s[j] = '\t';
                    i++;
                }
                break;
            default:
                s[j] = t[i];
        }
    }
    s[i] = '\0';
}