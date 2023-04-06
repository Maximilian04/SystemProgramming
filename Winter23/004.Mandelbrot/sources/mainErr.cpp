#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <immintrin.h>

__m256i mmy256_set123() {
    printf("run0\n");
    __m256i res = { 0 };

    printf("run1\n");
    for (int32_t i = 0; i < 8; ++i) {
        ((int32_t*)&res)[i] = i;
    }

    printf("run0\n");
    return res;
}

const __m256i ADDSEQ /**/ = mmy256_set123();
const __m256i ONESEQ /**/ = _mm256_set1_epi32(1);

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
