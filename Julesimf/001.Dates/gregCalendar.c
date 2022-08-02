#include "gregCalendar.h"

bool gregCalendar_isYearLeap(int year) {
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

int gregCalendar_monthDuration(int month, bool isLeap) {
    switch (month) {
    case 1:
        return 31;
    case 2:
        return 28 + isLeap;
    case 3:
        return 31;
    case 4:
        return 30;
    case 5:
        return 31;
    case 6:
        return 30;
    case 7:
        return 31;
    case 8:
        return 31;
    case 9:
        return 30;
    case 10:
        return 31;
    case 11:
        return 30;
    case 12:
        return 31;
    }
}

int gregCalendar_year2i(int year) {
    year--;
    return year * 365 + year / 4 - year / 100 + year / 400;
}

int gregCalendar_month2i(int month, bool isLeap) {
    month--;
    int res = 0;
    switch (month) {
    case 11:
        res += 30;
    case 10:
        res += 31;
    case 9:
        res += 30;
    case 8:
        res += 31;
    case 7:
        res += 31;
    case 6:
        res += 30;
    case 5:
        res += 31;
    case 4:
        res += 30;
    case 3:
        res += 31;
    case 2:
        res += 28 + isLeap;
    case 1:
        res += 31;
    }

    return res;
}

int gregCalendar_day2i(int day) {
    day--;
    return day;
}
