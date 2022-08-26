/**
 * @file strLib.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Functions to work with c-style strings
 * @date 2022-08-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef STRLIB_H
#define STRLIB_H

namespace strLib {
    int strlen(const char* str);
    char* strncpy(char* dst, const char* src, int count);
    char* strncat(char* dst, const char* src, int count);
}

#endif // STRLIB_H
