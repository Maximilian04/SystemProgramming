#include "Sort.h"

#include "include.h"

int main() {
    SCAN_ARR;
    // for (int i = 0; i < size; ++i)
        // cout << arr[i] << " ";
    // cout << endl;

    TIMEPOINT(tpBegin);

    sortArr(arr, size);

    TIMEPOINT(tpEnd);

    cout << TESTNAME << " done" << endl;
    LOGRESULT;
    cout << TESTNAME << " done" << endl;
    // for (int i = 0; i < size; ++i)
        // cout << arr[i] << " ";
    // cout << endl;

    free(arr);
}
