#include "Sort.h"

#include "include.h"

int main() {
    SCAN_ARR;

    TIMEPOINT(tpBegin);

    sortArr(arr, size);

    TIMEPOINT(tpEnd);

    LOGRESULT;

    free(arr);
}
