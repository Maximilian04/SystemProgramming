#include "date.h"

#include "gregCalendar.h"

#include <stdio.h>

void date_scan(struct date* date) {
    scanf("%d.%d.%d", &date->day, &date->month, &date->year);
}

void printFormattedInt(int out) {
    if (out <= 9) {
        printf("0%d", out);
    } else {
        printf("%d", out);
    }
}

void date_print(struct date date) {
    printFormattedInt(date.day);
    printf(".");
    printFormattedInt(date.month);
    printf(".");
    printFormattedInt(date.year);
    printf("\n");
}

int date_date2i(struct date date) {
    return gregCalendar_day2i(date.day) +
        gregCalendar_month2i(date.month, gregCalendar_isYearLeap(date.year)) +
        gregCalendar_year2i(date.year);
}

//struct date date_i2date(int i) {
//    return (struct date) { 0, 0, 0 };
//}

bool date_less(struct date first, struct date second) {
    if (first.year < second.year) {
        return true;
    } else if (first.year > second.year) {
        return false;
    }

    if (first.month < second.month) {
        return true;
    } else if (first.month > second.month) {
        return false;
    }

    if (first.day < second.day) {
        return true;
    }
    return false;
}

bool date_equal(struct date first, struct date second) {
    return (
        first.day == second.day &&
        first.month == second.month &&
        first.year == second.year);
}

struct date date_sub(struct date date1, struct date date2) {
    struct date res = { 0, 0, 0 };
    res.day = date1.day - date2.day;
    res.month = date1.month - date2.month;
    res.year = date1.year - date2.year;

    return res;
}

struct date date_add(struct date date1, struct date date2) {
    struct date res = { 0, 0, 0 };
    res.day = date1.day + date2.day;
    res.month = date1.month + date2.month;
    res.year = date1.year + date2.year;

    return res;
}

int date_calcDuration(struct date begin, struct date end) {
    return date_date2i(end) - date_date2i(begin);
}

struct date date_calcInterval(struct date begin, struct date end) {
    struct date interval = date_sub(end, begin);

    if (interval.day < 0) {
        interval.month--;
        interval.day += gregCalendar_monthDuration(
            (end.month + 11) % 12,
            gregCalendar_isYearLeap(end.month == 1 ? end.year - 1 : end.year));
    }

    if (interval.month < 0) {
        interval.year--;
        interval.month += 12;
    }

    return interval;
}
