#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "pervert.h"

const char FILE_NAME[] = "EvgeniyOnegin.txt";
const char FILE_ALPH_NAME[] = "alphabet.txt";
const char FILE_OUT_NAME[] = "build\\PunyEvgeniyOnegin.txt";

namespace pervert {
    ListOfLines linesOfPoem     = { nullptr, nullptr, 0 };
    ListOfLines linesOfAlphabet = { nullptr, nullptr, 0 };
    FILE* outFile = nullptr; ///< File for output

    enum CmpCyrillicResult {
        BAD_A,
        BAD_B,
        BAD_BOTH,
        LESSER,
        GREATER,
        EQV,
    };

    int getCyrillicIndex(const char a);
    CmpCyrillicResult cmpCyrillic(const char a, const char b);
    int cmpLinesStr(const char* a, const char* b);
    int cmpLinesBackStr(const char* a, const char* b);
    int cmpLinesRealNum(const char* a, const char* b);
    int cmpLines(const void* a, const void* b);
    int cmpLinesBack(const void* a, const void* b);
    int cmpLinesRealNum(const void* a, const void* b);
    void uq_sort(void* arr, int size, int begin, int end, int(*cmp)(const void*, const void*));

    enum {
        BAD_CHAR = -1,
    };

    int getCyrillicIndex(const char a) {
        for (int i = 0; i < linesOfAlphabet.size; ++i) {
            if (
                a == linesOfAlphabet.lines[i].str[0]
                )
                return i;
        }

        return BAD_CHAR;
    }

    CmpCyrillicResult cmpCyrillic(const char a, const char b) {
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

    int cmpLinesBackStr(const char* a, const char* b) {
        int iA = 0;
        int iB = 0;
        while (a[iA] != '\0') ++iA;
        while (b[iB] != '\0') ++iB;
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
        return cmpLinesBackStr(((const Line*)a)->str, ((const Line*)b)->str);
    }

    int cmpLinesRealNum(const void* a, const void* b) {
        if (((const Line*)a)->str < ((const Line*)b)->str) {
            return -1;
        }
        if (((const Line*)a)->str > ((const Line*)b)->str) {
            return 1;
        }
        return 0;
    }

    void uq_sort(void* arr, int begin, int end, int(*cmp)(const void*, const void*), int size);

    void uq_sort(void* arr, int begin, int end, int(*cmp)(const void*, const void*), int size) {
        if (begin >= end) {
            return;
        }

        int baseI = (begin + end) / 2;

        int l = begin;
        int r = end;

        void* tmp = calloc(1, size);

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
            memcpy(tmp,                   (char*)arr + l * size, size);
            memcpy((char*)arr + l * size, (char*)arr + r * size, size);
            memcpy((char*)arr + r * size, tmp,                   size);
            
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

    /**
     * @brief Sort lines with its beginning
     *
     */
    void sortLinesBeginning() {
        //qsort(linesOfPoem.lines, linesOfPoem.size, sizeof(Line), cmpLines);
        uq_sort(linesOfPoem.lines, 0, linesOfPoem.size - 1, cmpLines, sizeof(Line));
    }

    /**
     * @brief Sort lines with its number in raw poem
     *
     */
    void sortLinesReal() {
        //qsort(linesOfPoem.lines, linesOfPoem.size, sizeof(Line), cmpLinesRealNum);
        uq_sort(linesOfPoem.lines, 0, linesOfPoem.size - 1, cmpLinesRealNum, sizeof(Line));
    }

    /**
     * @brief Sort lines with its ending
     *
     */
    void sortLinesEnding() {
        //qsort(linesOfPoem.lines, linesOfPoem.size, sizeof(Line), cmpLinesBack);
        uq_sort(linesOfPoem.lines, 0, linesOfPoem.size - 1, cmpLinesBack, sizeof(Line));
    }

    /**
     * @brief Prints listOfLines to output in current state
     *
     */
    void writeOutPoem() {
        for (int listI = 0; listI < linesOfPoem.size; ++listI) {
            fprintf(outFile, "%s\n", linesOfPoem.lines[listI].str);
        }
    }

    /**
     * @brief Read linesOfPoem from file
     *
     */
    void uploadPoem() {
        listOfLines::uploadList(&linesOfPoem, FILE_NAME);
    }

    /**
     * @brief Upload cyrillic alphabet from file
     *
     */
    void uploadAlphabet() {
        listOfLines::uploadList(&linesOfAlphabet, FILE_ALPH_NAME);
    }

    /**
     * @brief Open output file
     *
     */
    void openOutFile() {
        assert(outFile == nullptr);
        outFile = fopen(FILE_OUT_NAME, "wt");
        assert(outFile != nullptr);
    }

    /**
     * @brief Close output file
     *
     */
    void closeOutFile() {
        assert(outFile != nullptr);
        fclose(outFile);
    }

    /**
     * @brief Free memory used by poem and alphabet
     *
     */
    void destroyAll() {
        destroyPoem();
        destroyAlphabet();
    }

    /**
     * @brief Free memory used by linesOfPoem
     *
     */
    void destroyPoem() {
        listOfLines::destroyList(&linesOfPoem);
    }

    /**
     * @brief Free memory used by linesOfAlphabet
     *
     */
    void destroyAlphabet() {
        listOfLines::destroyList(&linesOfAlphabet);
    }
}
