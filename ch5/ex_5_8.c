/**
 * There is no error checking in day_of_year or month_day. Rememdy this defect.
 */

#include <stdio.h>

static char daytab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int is_leap_year(int year);

// day_of_year: set day of year from month and day
int day_of_year(int year, int month, int day) {
    if (month < 1 || month > 12) {
        printf("Invalid month: %i\n", month);
        return -1;
    }

    int leap = is_leap_year(year);
    if (day < 1 || day > daytab[leap][month]) {
        printf("Invalid day: %i\n", day);
        return -1;
    }

    for (int i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

// month_day: set month, day from day of year
int month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = is_leap_year(year);
    int days_in_year = leap ? 366 : 365;
    if (yearday < 1 || yearday > days_in_year) {
        printf("Invalid day: %i", yearday);
        return -1;
    }

    int i;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
    return 0;
}

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}