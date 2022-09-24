/**
 * @file logger.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Logging system
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

namespace logger {
    void logHtmlHead(FILE* logFile);
    void logHtmlTail(FILE* logFile);

    void beginBlock(FILE* logFile);
    void endBlock(FILE* logFile);

    void logStr(FILE* logFile, const char* const str);
}

#endif // LOGGER_H
