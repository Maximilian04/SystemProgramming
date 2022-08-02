#include <stdbool.h>

bool gregCalendar_isYearLeap(int year);
int gregCalendar_monthDuration(int month, bool isLeap);

int gregCalendar_year2i(int year);
int gregCalendar_month2i(int month, bool isLeap);
int gregCalendar_day2i(int day);
