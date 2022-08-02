#include <stdbool.h>

struct date {
    int day;
    int month;
    int year;
};

void date_scan(struct date* date);
void date_print(struct date date);

int date_date2i(struct date date);
//struct date date_i2date(int i);

bool date_less(struct date first, struct date second);
bool date_equal(struct date first, struct date second);
struct date date_sub(struct date date1, struct date date2);
struct date date_add(struct date date1, struct date date2);

int date_calcDuration(struct date begin, struct date end);
struct date date_calcInterval(struct date begin, struct date end);
