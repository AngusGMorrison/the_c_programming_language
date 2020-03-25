/**
 * Rewrite the routines day_of_year and month_day with pointers instead of
 * indexing.
 */

#include <stdio.h>
#include <stdlib.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    printf("%i\n", day_of_year(2020, 2, 29));

    int *pmonth = malloc(sizeof(int));
    int *pday = malloc(sizeof(int));

    month_day(2020, 60, pmonth, pday);
    printf("%i/%i\n", *pmonth, *pday);
    free(pmonth);
    free(pday);
}

static char daytab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int is_leap_year(int year);

int day_of_year(int year, int month, int day) {
    int leap = is_leap_year(year);
    char *days_in_months = *(daytab + leap);

    while (--month)
        day += *++days_in_months;
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = is_leap_year(year);
    char *days_in_months = *(daytab + leap);

    while (yearday > *++days_in_months)
        yearday -= *days_in_months;

    *pmonth = days_in_months - *(daytab + leap);
    *pday = yearday;
}

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}