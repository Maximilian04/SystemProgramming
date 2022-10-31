/**
 * @file strFParser.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Formatted string parses
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef STRFPARSER_H
#define STRFPARSER_H

#include <stddef.h>

const int LINE_BUFFER_SIZE = 512;

namespace strFParser {
    const char* parseFCalloc(const char* format, ...);
    const char* parseFNBuf(size_t bufferNum, const char* format, ...);
    size_t addCallocBuf();
    void freeCalloc();
}

#endif // STRFPARSER_H
