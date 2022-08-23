
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

    //// int date_calcDuration(Date begin, Date end);
    //TEST_COMPARE(
    //    date_calcDuration((Date) { 1, 1, 1 }, (Date) { 2, 2, 2 }),
    //    397);

    //// Date date_calcInterval(Date begin, Date end);
    //TEST_VIACOMPARATOR(
    //    date_calcInterval((Date) { 1, 1, 1 }, (Date) { 3, 3, 3 }),
    //    ((Date) {
    //    2, 2, 2
    //}),
    //     date_equal);

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
