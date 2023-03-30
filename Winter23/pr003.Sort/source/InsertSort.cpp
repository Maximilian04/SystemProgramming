#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Sort.h"

void sortArr(int* arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = i - 1; j >= 0 && arr[j] > arr[j + 1]; --j) {
            swap(arr, j, j + 1);
        }
    }
}
