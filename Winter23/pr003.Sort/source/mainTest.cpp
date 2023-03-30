#include "Sort.h"

#include "include.h"

int main() {
    SCAN_ARR;

    cout << "size = " << size << endl;

    TIMEPOINT(tpBegin);

    sortArr(arr, size);

    TIMEPOINT(tpEnd);

    cout << "finished" << endl;

    LOGRESULT;

    free(arr);
}
