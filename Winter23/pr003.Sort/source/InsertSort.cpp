#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Sort.h"

inline void swap(int* arr, size_t i, size_t j) {
                      //(a)  (b)
    arr[i] -= arr[j]; //(a-b)(b)
    arr[j] += arr[j]; //(a-b)(a)
    arr[i] = arr[j] - arr[i]; 
                      //(b)  (a)
}

void sortArr(int* arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = i - 1; j >= 0 && arr[j] > arr[j + 1]; --j) {
            swap(arr, i, j);
        }
    }
}
