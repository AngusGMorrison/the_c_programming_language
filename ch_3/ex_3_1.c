#include <stdio.h>
#include <time.h>

/** Our binary search makes two tests inside the loop, when one would suffice
 * (at the price of more tests outside). Write a version with only one test
 * inside the loop and measure the difference in runtime.
 */

#define MAX_TEST_DATA 100000
#define TEST_RUNS 5000000

int one_check_bin_search(int x, int v[], int n);
int two_check_bin_search(int x, int v[], int n);
double get_secs(clock_t start, clock_t end);

int main() {
    int test_data[MAX_TEST_DATA];

    for (int i = 0; i < MAX_TEST_DATA; i++) {
        test_data[i] = i;
    }
    
    clock_t start = clock();
    for (int i = 0; i < TEST_RUNS; i++) {
        one_check_bin_search(4, test_data, MAX_TEST_DATA);
    }
    clock_t end = clock();
    printf("1 check in loop: %f\n", get_secs(start, end));

    start = clock();
    for (int i = 0; i < TEST_RUNS; i++) {
        two_check_bin_search(4, test_data, MAX_TEST_DATA);
    }
    end = clock();
    printf("2 checks in loop: %f\n", get_secs(start, end));
}

int one_check_bin_search(int x, int v[], int n) {
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return (v[mid] == x) ? mid : -1;
}

int two_check_bin_search(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

double get_secs(clock_t start, clock_t end) {
    return (double) (end - start) / CLOCKS_PER_SEC;
}