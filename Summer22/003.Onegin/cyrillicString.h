/**
 * @file CyrillicString.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Functions for comparing cyrillic strings
 * @date 2022-09-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CYRILLICSTRING_H
#define CYRILLICSTRING_H

#include "ListOfLines.h"

namespace cyrillicString {
    extern const ListOfLines* linesOfAlphabet;

    enum CmpCyrillicResult {
        BAD_A,
        BAD_B,
        BAD_BOTH,
        LESSER,
        GREATER,
        EQV,
    };

    enum {
        BAD_CHAR = -1,
    };

    void setAlphabet(const ListOfLines* linesOfAlphabet);

    int getCyrillicIndex(const char a);
    CmpCyrillicResult cmpCyrillic(const char a, const char b);
    int cmpLinesStr(const char* a, const char* b);
    int cmpLinesBackStr(const char* a, const char* b, int aLength, int bLength);
    int cmpLines(const void* a, const void* b);
    int cmpLinesBack(const void* a, const void* b);
}

void uq_sort(void* arr, int begin, int end, int(*cmp)(const void*, const void*), int size);

#endif // CYRILLICSTRING_H
