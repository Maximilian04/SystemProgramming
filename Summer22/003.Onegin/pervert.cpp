#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "pervert.h"

const char FILE_NAME[] = "EvgeniyOnegin.txt";
const char FILE_ALPH_NAME[] = "alphabet.txt";
const char FILE_OUT_NAME[] = "build\\PunyEvgeniyOnegin.txt";

namespace pervert {
    ListOfLines listOfLines = { {}, 0 };
    ListOfLines listOfAlphabet = { {}, 0 };
    FILE* outFile = nullptr; ///< File for output

    void qsortLinesBegining(int begin, int end);
    int cmpLinesStr(const char* a, const char* b);
    int cmpLines(const void* a, const void* b);
    bool isCyrilic(const char a);

    bool isCyrilic(const char a) {
        for (int i = 0; i < listOfAlphabet.size; ++i) {
            if (
                a == listOfAlphabet.lines[i].str[0]
                )
                return true;
        }

        return false;

        return
            a >= listOfAlphabet.lines[0].str[0] &&
            a <= listOfAlphabet.lines[listOfAlphabet.size - 1].str[0];
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
                    if (!isCyrilic(a[iA])) {
                        ++iA;
                        continue;
                    }
                    if (!isCyrilic(b[iB])) {
                        ++iB;
                        continue;
                    }
                    if (a[iA] < b[iB]) {
                        return -1;
                    } else if (a[iA] > b[iB]) {
                        return 1;
                    } else {
                        ++iA;
                        ++iB;
                    }
                }
            }
        }

        return 0;
    }

    int cmpLines(const void* a, const void* b) {
        //return strcmp(((const Line*)a)->str, ((const Line*)b)->str);
        return cmpLinesStr(((const Line*)a)->str, ((const Line*)b)->str);
    }

    /**
     * @brief Sorting algorithm for array
     *
     * @param begin Index of the first element to be sorted
     * @param end Index of the last element to be sorted
     */
    void qsortLinesBegining(int begin, int end) {
        /*if (begin < end) {
            int baseI = (begin + end) / 2;
            Line base;
            base.lenght = listOfLines.lines[baseI].lenght;
            base.str = strdup(listOfLines.lines[baseI].str);

            int i = begin;
            int j = end;

            while (i <= j) {
                while (isLineLesser(&listOfLines.lines[i], &base)) ++i;
                while (isLineGreater(&listOfLines.lines[j], &base)) --j;
                if (i >= j) break;

                // swap
                Line tmp = listOfLines.lines[j];
                listOfLines.lines[j] = listOfLines.lines[i];
                listOfLines.lines[i] = tmp;

                ++i;
                --j;
            }

            free(base.str);

            qsortLinesBegining(begin, j);
            qsortLinesBegining(j + 1, end);
        }*/
    }

    /**
     * @brief
     *
     */
    void sortLinesBeginning() {
        //qsortLinesBegining(0, listOfLines.size - 1);
        qsort(listOfLines.lines, listOfLines.size, sizeof(Line), cmpLines);
    }

    /**
     * @brief
     *
     */
    void sortLinesEnding() {

    }

    /**
     * @brief Prints listOfLines to output in current state
     *
     */
    void writeOutPoem(WritingPos pos) {
        switch (pos) {
        case WritingPos::BEGIN:
            fseek(outFile, 0, SEEK_SET);
            break;
        case WritingPos::END:
            fseek(outFile, 0, SEEK_END);
            break;
        default:
            assert(false && "WritingPos is who???");
        }

        for (int listI = 0; listI < listOfLines.size; ++listI) {
            fprintf(outFile, "%s\n", listOfLines.lines[listI].str);
        }
    }

    void uploadAlphabet() {
        assert(listOfAlphabet.size == 0);
        listOfAlphabet.lines = (Line*)calloc(MAX_LINE_NUMBER, sizeof(Line));

        FILE* file = fopen(FILE_ALPH_NAME, "r");
        listOfAlphabet.size = 0;
        while (listOfAlphabet.size < MAX_LINE_NUMBER) {
            listOfAlphabet.lines[listOfAlphabet.size].str = (char*)calloc(EXTRA_BUFFER_SIZE, sizeof(char));
            int fscanfRes = fscanf(file, "%" EXTRA_BUFFER_SIZE_ "[^\n]", listOfAlphabet.lines[listOfAlphabet.size].str);
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
        assert(listOfAlphabet.size < MAX_LINE_NUMBER);
    }

    /**
     * @brief Open output file
     *
     */
    void openOutFile() {
        assert(outFile == nullptr);
        outFile = fopen(FILE_OUT_NAME, "w");
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
        listOfLines.lines = (Line*)calloc(MAX_LINE_NUMBER, sizeof(Line));

        FILE* file = fopen(FILE_NAME, "r");
        listOfLines.size = 0;
        while (listOfLines.size < MAX_LINE_NUMBER) {
            listOfLines.lines[listOfLines.size].str = (char*)calloc(EXTRA_BUFFER_SIZE, sizeof(char));
            int fscanfRes = fscanf(file, "%" EXTRA_BUFFER_SIZE_ "[^\n]", listOfLines.lines[listOfLines.size].str);
            fgetc(file);

            if (fscanfRes == EOF) {
                break;
            } else if (fscanfRes == 0) {
                continue;
            } else if (fscanfRes != 1) {
                assert(false && "fscanf returned ???");
            }

            listOfLines.lines[listOfLines.size].lenght = (int)strlen(listOfLines.lines[listOfLines.size].str);
            listOfLines.size++;
        }
        fclose(file);
        assert(listOfLines.size < MAX_LINE_NUMBER);
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
}
