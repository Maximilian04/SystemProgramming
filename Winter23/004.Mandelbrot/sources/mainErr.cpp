#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <immintrin.h>

int main() {
    __m128i arr1;
    printf("Point 1\n");

    __m128i arr2 = { 0 };
    printf("Point 2\n");

    __m256 arr3;
    printf("Point 3\n");

    __m256 arr4 = { 0 };
    printf("Point 4\n");

    __m256i arr7;
    printf("Point 7\n");

    __m256i arr8 = { 0 };
    printf("Point 8\n");

    /*__m512 arr5;
    printf("Point 5\n");

    __m512 arr6 = { 0 };
    printf("Point 6\n");*/

    printf("Program finished 0\n");
    return 0;
}
