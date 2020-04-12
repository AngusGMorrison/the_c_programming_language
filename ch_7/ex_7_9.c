/**
 * Functions like isupper can be implemented to save space or to save time.
 * Explore both possibilities.
 */

// Macro saves time with no function call, but expands into more space
#define time_save_isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

/* Saves space as function is not expanded each time it is called, but the call
   takes more time. */
int isupper(char c) {
    return (c >= 'A' && c <= 'Z');
}