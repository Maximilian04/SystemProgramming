#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "cyrillicString.h"

namespace cyrillicString {
    const ListOfLines* linesOfAlphabet = nullptr;

    void setAlphabet(const ListOfLines* linesOfAlphabetPtr) {
        cyrillicString::linesOfAlphabet = linesOfAlphabetPtr;
    }

    int getCyrillicIndex(const char a) {
        assert(linesOfAlphabet != nullptr);

        for (int i = 0; i < linesOfAlphabet->size; ++i) {
            if (a == linesOfAlphabet->lines[i].str[0])
                return i;
        }

        return BAD_CHAR;
    }

    CmpCyrillicResult cmpCyrillic(const char a, const char b) {
        assert(linesOfAlphabet != nullptr);

        int aIndex = getCyrillicIndex(a);
        int bIndex = getCyrillicIndex(b);

        if (aIndex == BAD_CHAR && bIndex != BAD_CHAR) {
            return CmpCyrillicResult::BAD_A;
        }
        if (aIndex != BAD_CHAR && bIndex == BAD_CHAR) {
            return CmpCyrillicResult::BAD_B;
        }
        if (aIndex == BAD_CHAR && bIndex == BAD_CHAR) {
            return CmpCyrillicResult::BAD_BOTH;
        }
        if (aIndex < bIndex) {
            return CmpCyrillicResult::LESSER;
        }
        if (aIndex > bIndex) {
            return CmpCyrillicResult::GREATER;
        }
        return CmpCyrillicResult::EQV;
    }

    int cmpLinesStr(const char* a, const char* b) {
        int iA = 0;
        int iB = 0;
        while (true) {
            if (a[iA] == '\0') {
                if (b[iB] == '\0') {
                    return 0;
                } else {
                    return -1;
                }
            } else {
                if (b[iB] == '\0') {
                    return 1;
                } else {
                    switch (cmpCyrillic(a[iA], b[iB])) {
                    case CmpCyrillicResult::BAD_A:
                        ++iA;
                        continue;
                        break;
                    case CmpCyrillicResult::BAD_B:
                        ++iB;
                        continue;
                        break;
                    case CmpCyrillicResult::BAD_BOTH:
                        ++iA;
                        ++iB;
                        continue;
                        break;
                    case CmpCyrillicResult::LESSER:
                        return -1;
                        break;
                    case CmpCyrillicResult::GREATER:
                        return 1;
                        break;
                    case CmpCyrillicResult::EQV:
                        ++iA;
                        ++iB;
                        break;
                    default:
                        assert(false);
                    }
                }
            }
        }

        return 0;
    }

    int cmpLinesBackStr(const char* a, const char* b, int aLength, int bLength) {
        int iA = aLength;
        int iB = bLength;
        while (true) {
            if (iA == -1) {
                if (iB == -1) {
                    return 0;
                } else {
                    return -1;
                }
            } else {
                if (iB == -1) {
                    return 1;
                } else {
                    switch (cmpCyrillic(a[iA], b[iB])) {
                    case CmpCyrillicResult::BAD_A:
                        --iA;
                        continue;
                        break;
                    case CmpCyrillicResult::BAD_B:
                        --iB;
                        continue;
                        break;
                    case CmpCyrillicResult::BAD_BOTH:
                        --iA;
                        --iB;
                        continue;
                        break;
                    case CmpCyrillicResult::LESSER:
                        return -1;
                        break;
                    case CmpCyrillicResult::GREATER:
                        return 1;
                        break;
                    case CmpCyrillicResult::EQV:
                        --iA;
                        --iB;
                        break;
                    default:
                        assert(false);
                    }
                }
            }
        }

        return 0;
    }

    int cmpLines(const void* a, const void* b) {
        return cmpLinesStr(((const Line*)a)->str, ((const Line*)b)->str);
    }

    int cmpLinesBack(const void* a, const void* b) {
        return cmpLinesBackStr(((const Line*)a)->str, ((const Line*)b)->str, ((const Line*)a)->lenght, ((const Line*)b)->lenght);
    }
}

void memswap(void* aVoid, void* bVoid, size_t size); ///< Fast memory swapping

void memswap(void* aVoid, void* bVoid, size_t size) {
    char* aPtr = (char*)aVoid;
    char* bPtr = (char*)bVoid;
    size_t sizeDone = 0;

    uint64_t tmp64 = 0;
    while ((sizeDone - size) >> sizeof(uint64_t)) {
        tmp64                         = *(uint64_t*)(aPtr + sizeDone);
        *(uint64_t*)(aPtr + sizeDone) = *(uint64_t*)(bPtr + sizeDone);
        *(uint64_t*)(bPtr + sizeDone) = tmp64;

        sizeDone += sizeof(uint64_t);
    }

    uint32_t tmp32 = 0;
    while ((sizeDone - size) >> sizeof(uint32_t)) {
        tmp32                         = *(uint32_t*)(aPtr + sizeDone);
        *(uint32_t*)(aPtr + sizeDone) = *(uint32_t*)(bPtr + sizeDone);
        *(uint32_t*)(bPtr + sizeDone) = tmp32;

        sizeDone += sizeof(uint32_t);
    }
    
    uint16_t tmp16 = 0;
    while ((sizeDone - size) >> sizeof(uint16_t)) {
        tmp16                         = *(uint16_t*)(aPtr + sizeDone);
        *(uint16_t*)(aPtr + sizeDone) = *(uint16_t*)(bPtr + sizeDone);
        *(uint16_t*)(bPtr + sizeDone) = tmp16;

        sizeDone += sizeof(uint16_t);
    }

    uint8_t tmp8 = 0;
    while ((sizeDone - size) >> sizeof(uint8_t)) {
        tmp8                         = *(uint8_t*)(aPtr + sizeDone);
        *(uint8_t*)(aPtr + sizeDone) = *(uint8_t*)(bPtr + sizeDone);
        *(uint8_t*)(bPtr + sizeDone) = tmp8;

        sizeDone += sizeof(uint8_t);
    }
}

void uq_sort(void* arr, int begin, int end, int(*cmp)(const void*, const void*), int size) {
    if (begin >= end) {
        return;
    }

    int baseI = (begin + end) / 2;

    int l = begin;
    int r = end;

    void* tmp = calloc(1, size);
    assert(tmp != nullptr);

    while (l < r) {
        while (cmp((char*)arr + l * size, (char*)arr + baseI * size) == -1) ++l;
        while (cmp((char*)arr + r * size, (char*)arr + baseI * size) == +1) --r;

        if (l >= r) {
            break;
        }

        // swap
        if (l == baseI) {
            baseI = r;
        } else if (r == baseI) {
            baseI = l;
        }
        memswap((char*)arr + l * size, (char*)arr + r * size, size);
            
        // Ифы имени Миши
        if (l != baseI)
            ++l;
        if (r != baseI)
            --r;
    }

    free(tmp);

    for (int i = begin; i <= baseI; ++i) {
        assert(cmp((char*)arr + i * size, (char*)arr + baseI * size) <= 0 || (printf("%d %d", i, baseI), false));
    }
    for (int i = baseI; i <= end; ++i) {
        assert(cmp((char*)arr + i * size, (char*)arr + baseI * size) >= 0 || (printf("%d %d", i, baseI), false));
    }

    uq_sort(arr, begin, baseI - 1, cmp, size);
    uq_sort(arr, baseI + 1,   end, cmp, size);
}
