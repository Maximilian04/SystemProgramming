#include "date.h"

#include "gregCalendar.h"

#include <stdio.h>

void date_scan(Date* date) {
    scanf("%d.%d.%d", &date->day, &date->month, &date->year);
}

void date_print(Date date) {
    printf("%02d.%02d.%04d\n", date.day, date.month, date.year);
}

int date_date2i(Date date) {
    return gregCalendar_date2i(date);
}

//date date_i2date(int i) {
//    return (date) { 0, 0, 0 };
//}

bool date_less(Date first, Date second) {
    if (first.year < second.year) {
        return true;
    }
    if (first.year > second.year) {
        return false;
    }

    if (first.month < second.month) {
        return true;
    }
    if (first.month > second.month) {
        return false;
    }

    if (first.day < second.day) {
        return true;
    }
    return false;
}

bool date_equal(Date first, Date second) {
    return (
        first.day == second.day &&
        first.month == second.month &&
        first.year == second.year);
}

Date date_sub(Date date1, Date date2) {
    Date res = { 0, 0, 0 };
    res.day = date1.day - date2.day;
    res.month = date1.month - date2.month;
    res.year = date1.year - date2.year;

    return res;
}

Date date_add(Date date1, Date date2) {
    Date res = { 0, 0, 0 };
    res.day = date1.day + date2.day;
    res.month = date1.month + date2.month;
    res.year = date1.year + date2.year;

    return res;
}

int date_calcDuration(Date begin, Date end) {
    return date_date2i(end) - date_date2i(begin);
}

Date date_calcInterval(Date begin, Date end) {
    Date interval = date_sub(end, begin);

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
