#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Sort.h"

void sortArr(int* arr, size_t size) {
    bool swapped = true;
    for (size_t i = 0; swapped; ++i) {
        swapped = false;
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                swapped = true;
            }
        }
    }
}
