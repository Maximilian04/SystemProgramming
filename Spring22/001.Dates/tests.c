#include "date.h"
#include "gregCalendar.h"

#include <stdio.h>

#define TEST_COMPARE(RESULT, ANSWER) \
    if (RESULT != ANSWER) { \
    printf("TEST FAILED : %s : %s\n", #RESULT, #ANSWER); \
    }

#define TEST_VIACOMPARATOR(RESULT, ANSWER, COMPARATOR) \
if (!COMPARATOR(RESULT, ANSWER)) { \
    printf("TEST FAILED : %s : %s\n", #RESULT, #ANSWER); \
    }

int main() {

    // bool gregCalendar_isYearLeap(int year);
    TEST_COMPARE(
        gregCalendar_isYearLeap(2004),
        true);

    // bool gregCalendar_isYearLeap(int year);
    TEST_COMPARE(
        gregCalendar_isYearLeap(2005),
        false);

    // int gregCalendar_monthDuration(int month, bool isLeap);
    TEST_COMPARE(
        gregCalendar_monthDuration(2, true),
        29);

    // int gregCalendar_monthDuration(int month, bool isLeap);
    TEST_COMPARE(
        gregCalendar_monthDuration(2, false),
        28);

    // int gregCalendar_date2i(Date date);
    TEST_COMPARE(
        gregCalendar_date2i((Date) { 2, 2, 2 }),
        397);

    /*
        cannot be tested:

        void date_scan(Date* date);
        void date_print(Date date);
    */

    // int date_date2i(Date date);
    TEST_COMPARE(
        date_date2i((Date) { 2, 2, 2 }),
        397);

    // bool date_less(Date first, Date second);
    TEST_COMPARE(
        date_less((Date) { 1, 1, 1 }, (Date) { 2, 2, 2 }),
        true);

    // bool date_less(Date first, Date second);
    TEST_COMPARE(
        date_less((Date) { 2, 2, 2 }, (Date) { 1, 1, 1 }),
        false);

    // bool date_equal(Date first, Date second);
    TEST_COMPARE(
        date_equal((Date) { 1, 1, 1 }, (Date) { 1, 1, 1 }),
        true);

    // bool date_equal(Date first, Date second);
    TEST_COMPARE(
        date_equal((Date) { 2, 2, 2 }, (Date) { 1, 1, 1 }),
        false);

    // Date date_sub(Date date1, Date date2);
    TEST_VIACOMPARATOR(
        date_sub((Date) { 3, 3, 3 }, (Date) { 1, 1, 1 }),
        ((Date) {
        2, 2, 2
    }),
        date_equal);

    // Date date_add(Date date1, Date date2);
    TEST_VIACOMPARATOR(
        date_add((Date) { 3, 3, 3 }, (Date) { 1, 1, 1 }),
        ((Date) {
        4, 4, 4
    }),
        date_equal);

    // int date_calcDuration(Date begin, Date end);
    TEST_COMPARE(
        date_calcDuration((Date) { 1, 1, 1 }, (Date) { 2, 2, 2 }),
        397);

    // Date date_calcInterval(Date begin, Date end);
    TEST_VIACOMPARATOR(
        date_calcInterval((Date) { 1, 1, 1 }, (Date) { 3, 3, 3 }),
        ((Date) {
        2, 2, 2
    }),
        date_equal);

    //{ // Date date_sub(Date date1, Date date2);
    //    Date result = date_sub((Date) { 3, 3, 3 }, (Date) { 1, 1, 1 });
    //    Date answer = { 2, 2, 2 };
    //
    //    if (result.day != answer.day ||
    //        result.month != answer.month ||
    //        result.year != answer.year) {
    //        printf("\nTEST FAILED : date_sub((Date) { 3, 3, 3 }, (Date) { 1, 1, 1 })");
    //    }
    //}

    printf("TESTS ARE DONE\n");
    return 0;
}
