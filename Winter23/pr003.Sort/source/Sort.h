#ifndef SORT_H
#define SORT_H

void sortArr(int* arr, size_t size);

inline void swap(int* arr, size_t i, size_t j) {
                      //(a)  (b)
    arr[i] -= arr[j]; //(a-b)(b)
    arr[j] += arr[i]; //(a-b)(a)
    arr[i] = arr[j] - arr[i];
                      //(b)  (a)
}

#endif // SORT_H
