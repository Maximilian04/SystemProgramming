/**
 * @file logger.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Logging system
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef LOGGER_H
#define LOGGER_H

#include "stdio.h"

#include "strFParser.h"
#include "DebugInfo.h"

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

    void logStructHead(const char* structName, const void* objPtr);
    void logStructHeadDebug(const char* structName, const void* objPtr, const DebugInfo* debugPtr);


#define LOGGER__LOGFIELD_COLORED_GOODDATA(flag, obj) "= %s%"#flag" (POISON)%s", htmlCrimsonColorStart, obj, htmlCrimsonColorStop
#define LOGGER__LOGFIELD_COLORED_POISONED(flag, obj) "= %"#flag, obj
#define LOGGER__LOGFIELD_COLORED_BOTH(cmm) strFParser::parseFCalloc(cmm(printfFlag, fieldClass->fieldName))

#define logger__logField(fieldClass, fieldName, printfFlag, fieldPoison, ...) \
    logger::logField(#fieldName,  (fieldValue == fieldPoison) ?                \
        LOGGER__LOGFIELD_COLORED_BOTH(LOGGER__LOGFIELD_COLORED_POISONED) :      \
        LOGGER__LOGFIELD_COLORED_BOTH(LOGGER__LOGFIELD_COLORED_GOODDATA),        \
        __VA_OPT__(, __VA_ARGS__))

    void logField(const char* fieldName, const char* valueStr, int shift = 0);

    /*
#define logger__logFieldArray(fieldClass, fieldName, size, fieldType) logger::logFieldArray(\
           #fieldName, fieldClass->fieldName,   size, fieldClass::POISON##fieldType##PTR, fieldClass::POISON##fieldType
#define LOGGER_LOGFIELDARRAY_HDR(fieldType) void logFieldArray(\
const char* arrayName, fieldType* array, size_t size, fieldType*  POISON_CODEPTR,         fieldType   POISON_CODE, const char** labels

#define LOGGER_LOGFIELDARRAY_DEF(fieldType) LOGGER_LOGFIELDARRAY_HDR(fieldType) = nullptr
*/
    void addBlock();
    void endBlock();
    void addInvisibleBlock();
    void endInvisibleBlock();

    void logStr(const char* const str, int shiftW, int shiftH, int shiftHB);
    void logStr(const char* const str, int shiftW);
    void logStr(const char* const str, int shiftW, int shiftH);
    void logLine(const char* const str);
    void logLine(const char* const str, int shiftW, int shiftH);

    void emergencyLog(const char* const str);
    void logMsg(const char* const str);
}

#define COLORED_TEXT(color, text) "<font color=\"" color "\">" text "</font>"

#endif // LOGGER_H
