/**
 * @file strFParser.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Formatted string parses
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef STRFPARSER
#define STRFPARSER

const int LINE_BUFFER_SIZE = 256;

namespace strFParser {
    const char* parseF(const char* format, ...);
    const char* parseFCalloc(const char* format, ...);
    const char* parseFNBuf(int bufferNum, const char* format, ...);
    int addCallocBuf();
    void freeCalloc();
}

#endif // STRFPARSER
