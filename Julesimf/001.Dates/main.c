#include "date.h"

#include <stdio.h>

int main() {
    struct date date1, date2;
    struct date first, second;
    date_scan(&date1);
    date_scan(&date2);

    if (date_less(date1, date2)) {
        first = date1;
        second = date2;
    } else {
        first = date2;
        second = date1;
    }

    struct date interval = date_calcInterval(first, second);
    printf("Interval: %d years, %d months, %d days\n", interval.year, interval.month, interval.day);
    printf("Diff. %d days\n", date_calcDuration(first, second));

    return 0;
}
