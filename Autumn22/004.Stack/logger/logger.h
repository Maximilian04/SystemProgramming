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

#include "loggerIncludeDefines.h"

namespace logger {
    void setLogTarget(FILE* _logTarget);

    int openLogFile(const char* fileName);
    int openLogFile();
    int closeLogFile();


    void logHtmlHead();
    void logHtmlTail();
    void logFuncHead(LOGFUNCHEAD_PARAMS_H);
    void logStructHead(const char* structName, const void* onjPtr);

#define LOGGER_logFieldS(fieldClass, fieldName, shift) logger::logField(#fieldName, fieldClass->fieldName, shift)
#define LOGGER_logField(fieldClass, fieldName)         logger::logField(#fieldName, fieldClass->fieldName)
#define LOGGER_LOGFIELD_DEF(fieldType) void logField(const char* fieldName, fieldType fieldValue, int shift
    LOGGER_LOGFIELD_DEF(size_t) = 0);
#define LOGGER_LOGFIELDARRAY_DEF(fieldType) void logFieldArray(const char* arrayName,  fieldType* array, size_t size
#define LOGGER_logFieldArray(fieldClass, fieldName, size)    logger::logFieldArray(#fieldName, fieldClass->fieldName, size)
    LOGGER_LOGFIELDARRAY_DEF(int));

    void beginBlock();
    void endBlock();

    void logLine(const char* const str);
    void logStrS(const char* const str, int shift);
}

#endif // LOGGER_H
