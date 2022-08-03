#pragma once

#include <stdbool.h>

#include "date.h"

bool gregCalendar_isYearLeap(int year);
int gregCalendar_monthDuration(int month, bool isLeap);

// number of days since 01.01.0001
int gregCalendar_date2i(Date date);
