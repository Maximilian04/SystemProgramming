#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "pervert.h"

const char FILE_NAME[] = "EvgeniyOnegin.txt";
const char FILE_ALPH_NAME[] = "alphabet.txt";
const char FILE_OUT_NAME[] = "build\\PunyEvgeniyOnegin.txt";

namespace pervert {
    ListOfLines listOfLines = { nullptr, nullptr, 0 };
    ListOfLines listOfAlphabet = { nullptr, nullptr, 0 };
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
        for (int i = 0; i < listOfAlphabet.size; ++i) {
            if (
                a == listOfAlphabet.lines[i].str[0]
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
        //qsort(listOfLines.lines, listOfLines.size, sizeof(Line), cmpLines);
        uq_sort(listOfLines.lines, 0, listOfLines.size - 1, cmpLines, sizeof(Line));
    }

    /**
     * @brief Sort lines with its number in raw poem
     *
     */
    void sortLinesReal() {
        //qsort(listOfLines.lines, listOfLines.size, sizeof(Line), cmpLinesRealNum);
        uq_sort(listOfLines.lines, 0, listOfLines.size - 1, cmpLinesRealNum, sizeof(Line));
    }

    /**
     * @brief Sort lines with its ending
     *
     */
    void sortLinesEnding() {
        //qsort(listOfLines.lines, listOfLines.size, sizeof(Line), cmpLinesBack);
        uq_sort(listOfLines.lines, 0, listOfLines.size - 1, cmpLinesBack, sizeof(Line));
    }

    /**
     * @brief Prints listOfLines to output in current state
     *
     */
    void writeOutPoem() {
        for (int listI = 0; listI < listOfLines.size; ++listI) {
            fprintf(outFile, "%s\n", listOfLines.lines[listI].str);
        }
    }

    /**
     * @brief Upload cyrillic alphabet from file
     *
     */
    void uploadAlphabet() {
        assert(listOfAlphabet.size == 0);
        listOfAlphabet.lines = (Line*)calloc(9000, sizeof(Line));

        FILE* file = fopen(FILE_ALPH_NAME, "r");
        listOfAlphabet.size = 0;
        while (listOfAlphabet.size < 9000) {
            listOfAlphabet.lines[listOfAlphabet.size].str = (char*)calloc(100, sizeof(char));
            int fscanfRes = fscanf(file, "%" "100" "[^\n]", listOfAlphabet.lines[listOfAlphabet.size].str);
            fgetc(file);

            if (fscanfRes == EOF) {
                break;
            } else if (fscanfRes == 0) {
                continue;
            } else if (fscanfRes != 1) {
                assert(false && "fscanf returned ???");
            }

            listOfAlphabet.lines[listOfAlphabet.size].lenght = (int)strlen(listOfAlphabet.lines[listOfAlphabet.size].str);
            listOfAlphabet.size++;
        }
        fclose(file);
        assert(listOfAlphabet.size < 9000);
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
     * @brief Read ListOfLines from file
     *
     */
    void readListOfLines() {
        assert(listOfLines.size == 0);

        struct stat fileStat;

        int statResult = stat(FILE_NAME, &fileStat);
        FILE* file = fopen(FILE_NAME, "rt");
        assert(statResult == 0 && "Cannot get file info");
        assert(file != nullptr && "Cannot open file");

        listOfLines.firstVacant = (char*)calloc(fileStat.st_size + 1, sizeof(char));
        size_t freadResult = fread(listOfLines.firstVacant, sizeof(char), fileStat.st_size, file);
        listOfLines.firstVacant = (char*)realloc((void*)listOfLines.firstVacant, sizeof(char) * (freadResult + 1));
        listOfLines.firstVacant[freadResult] = '\0';

        //printf("%d %d\n", (int)freadResult, (int)fileStat.st_size);

        listOfLines.lines = (Line*)calloc(freadResult + 1, sizeof(Line));
        listOfLines.size = 0;

        do {
            listOfLines.lines[listOfLines.size].str = listOfLines.firstVacant;
            listOfLines.lines[listOfLines.size].lenght = 0;

            while (true) {
                int* indexPtr = &listOfLines.lines[listOfLines.size].lenght;
                char* symbPtr = &listOfLines.lines[listOfLines.size].str[*indexPtr];
                if (*symbPtr == '\n') {
                    *symbPtr = '\0';
                }
                if (*symbPtr == '\0') {
                    break;
                }
                (*indexPtr)++;
            }

            listOfLines.firstVacant += listOfLines.lines[listOfLines.size].lenght + 1;
            if (listOfLines.lines[listOfLines.size].lenght == 0) {
                continue;
            }
            listOfLines.size++;
        } while (listOfLines.firstVacant < (listOfLines.lines[0].str + freadResult + 1));

        fclose(file);

        //printf("%d\n", listOfLines.size);
        listOfLines.lines = (Line*)realloc(listOfLines.lines, sizeof(Line) * listOfLines.size);
    }

    /**
     * @brief Free memory used by listOfLines
     *
     */
    void destroyListOfLines() {
        for (int i = 0; i < listOfLines.size; ++i) {
            free(listOfLines.lines[i].str);
        }
        free(listOfLines.lines);
    }

    /**
     * @brief Free memory used by listAlphabet
     *
     */
    void destroyAlphabet() {
        for (int i = 0; i < listOfAlphabet.size; ++i) {
            free(listOfAlphabet.lines[i].str);
        }
        free(listOfAlphabet.lines);
    }
}
