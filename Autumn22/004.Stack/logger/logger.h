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
    void setLogTarget(FILE* _logTarget);

    int openLogFile(const char* fileName);
    int openLogFile();
    int closeLogFile();


    void logHtmlHead();
    void logHtmlTail();

#define LOGFUNCHEAD_ARGS_H            const char* funcName, const char* fileName, const int lineN
#define LOGFUNCHEAD_ARGS_R             __PRETTY_FUNCTION__,             __FILE__,        __LINE__
#define logger__logFuncHead() logger::logFuncHead(funcName,             fileName,           lineN
    void logFuncHead(LOGFUNCHEAD_ARGS_H);

    void logStructHead(const char* structName, const void* onjPtr);

#define logger__logField(fieldClass, fieldName) logger::logField(#fieldName, fieldClass->fieldName
#define LOGGER_LOGFIELD_DEF(fieldType) void logField(const char* fieldName, fieldType fieldValue, int shift
    LOGGER_LOGFIELD_DEF(size_t) = 0);

#define logger__logFieldArray(fieldClass, fieldName, size) logger::logFieldArray(#fieldName, fieldClass->fieldName, size
#define LOGGER_LOGFIELDARRAY_DEF(fieldType) void logFieldArray(const char* arrayName,  fieldType* array, size_t size
    LOGGER_LOGFIELDARRAY_DEF(int));

    void addBlock();
    void endBlock();
    void addInvisibleBlock();
    void endInvisibleBlock();

    void logStr(const char* const str, int shiftW, int shiftH, int shiftHB);
    void logStr(const char* const str, int shiftW);
    void logStr(const char* const str, int shiftW, int shiftH);
    void logLine(const char* const str);
    void logLine(const char* const str, int shiftW, int shiftH);
}

#endif // LOGGER_H
