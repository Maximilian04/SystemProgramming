#pragma once

#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

void date_scan(Date* date);
void date_print(Date date);

int date_date2i(Date date);
//date date_i2date(int i);

bool date_less(Date first, Date second);
bool date_equal(Date first, Date second);
Date date_sub(Date date1, Date date2);
Date date_add(Date date1, Date date2);

int date_calcDuration(Date begin, Date end);
Date date_calcInterval(Date begin, Date end);
