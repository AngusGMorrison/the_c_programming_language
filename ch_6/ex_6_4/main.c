/**
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence. Precede each word by its
 * count.
 */

#include "get_words.h"
#include "node.h"
#include "tree.h"

int main() {
    get_distinct_words();
    sort_words();
    print_distinct_words();
}