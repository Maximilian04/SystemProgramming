#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "logger.h"

#include "..\logger\loggerIncludeConsts.cpp"
#include "..\strFParser\strFParser.h"

static int numberOfDigits(size_t n) {
    int number = 0;
    for (number = 0; n; n /= 10, number++);
    return number;
}

namespace logger {
    static FILE* logTarget = nullptr;
    static int marginCounter = 0;

    void printLog(FILE* stream, const char* format, ...);
    void setLogTargetHard(FILE* _logTarget);



    void printLog(FILE* stream, const char* format, ...) {
        assert(stream != nullptr);
        assert(format != nullptr);

        va_list ap;
        va_start(ap, format);
        vfprintf(stream, format, ap);
        va_end(ap);
    }

    void setLogTargetHard(FILE* _logTarget) {
        logTarget = _logTarget;
    }

    void setLogTarget(FILE* _logTarget) {
        assert(_logTarget != nullptr);

        assert(logTarget == nullptr);
        setLogTargetHard(_logTarget);
    }

    int openLogFile(const char* fileName) {
        assert(fileName != nullptr);
        assert(logTarget == nullptr);

        FILE* file = 0;
        file = fopen(fileName, "at");
        if (file == nullptr)
            return 1;

        setvbuf(file, nullptr, _IONBF, 0);
        setLogTarget(file);
        return 0;
    }

    int openLogFile() {
        return openLogFile(logFileName);
    }

    int closeLogFile() {
        assert(logTarget != nullptr && logTarget != stdout);
        int fcloseRes = fclose(logTarget);
        setLogTargetHard(nullptr);
        return fcloseRes;
    }

    void logHtmlHead() {
        assert(logTarget != nullptr);
        printLog(logTarget, "%s",
            htmlHead);
    }

    void logHtmlTail() {
        assert(logTarget != nullptr);
        printLog(logTarget, "%s",
            htmlTail);
    }

    void logFuncHead(LOGFUNCHEAD_ARGS_H) {
        assert(funcName != nullptr);
        assert(fileName != nullptr);

        logger::logLine(strFParser::parseF("%s at %s (%d line)", funcName, fileName, lineN));
    }

    void logStructHead(const char* structName, const void* objPtr) {
        assert(structName != nullptr);

        logger::logLine(strFParser::parseF("%s[%s%p%s] \"stack1\" at main() at main.cpp (50 line):",
            structName, htmlCyanColorStart, objPtr, htmlCyanColorStop));
    }



#define LOGGER_LOGFIELD_IMPL(fieldType, flag)                                                       \
    LOGGER_LOGFIELD_DEF(fieldType)) {                                                                \
        assert(fieldName != nullptr);                                                                 \
                                                                                                       \
        logger::logLine(fieldName);                                                                     \
        logger::logStr(strFParser::parseF("= %"#flag, fieldValue), (int)strlen(fieldName) + 1 + shift);  \
    }
    LOGGER_LOGFIELD_IMPL(size_t, llu);






#define LOGGER_LOGFIELDARRAY_IMPL0(fieldType, flag)                                                               \
    LOGGER_LOGFIELDARRAY_DEF0(fieldType)) {                                                                        \
        assert(arrayName != nullptr);                                                                               \
        assert(array != nullptr);                                                                                    \
        assert(size < SIZE_MAX);                                                                                      \
                                                                                                                       \
        logger::logLine(strFParser::parseF("%s[%s%p%s]:", arrayName, htmlCyanColorStart, array, htmlCyanColorStop));    \
        logger::addBlock();                                                                                              \
        int digitsNumber = numberOfDigits(size - 1);                                                                      \
        int parseBufferNum = strFParser::addCallocBuf();                                                                   \
        for (size_t elemI = 0; elemI < size; ++elemI) {                                                                     \
                logger::logLine(strFParser::parseF(strFParser::parseFNBuf(parseBufferNum, "[%%%dd]", digitsNumber), elemI)); \
                logger::logStr(strFParser::parseF("= %"#flag, array[elemI]), 3 + digitsNumber);                               \
        }                                                                                                                      \
        strFParser::freeCalloc();                                                                                               \
        logger::endBlock();                                                                                                      \
    }
    LOGGER_LOGFIELDARRAY_IMPL0(int, d);


#define LOGGER_LOGFIELDARRAY_IMPL1(fieldType, flag)                                                              \
    LOGGER_LOGFIELDARRAY_DEF1(fieldType)) {                                                                       \
        assert(arrayName != nullptr);                                                                              \
        assert(labels != nullptr);                                                                                  \
        assert(array != nullptr);                                                                                    \
        assert(size < SIZE_MAX);                                                                                      \
                                                                                                                       \
        logger::logLine(strFParser::parseF("%s[%s%p%s]:", arrayName, htmlCyanColorStart, array, htmlCyanColorStop));    \
        logger::addBlock();                                                                                              \
        int digitsNumber = numberOfDigits(size - 1);                                                                      \
        int parseBufferNum = strFParser::addCallocBuf();                                                                   \
        for (size_t elemI = 0; elemI < size; ++elemI) {                                                                     \
                logger::logLine(strFParser::parseF(strFParser::parseFNBuf(parseBufferNum, "[%%%dd]", digitsNumber), elemI)); \
                logger::logStr(strFParser::parseF("= %"#flag, array[elemI]), 3 + digitsNumber);                               \
                if (labels[elemI] == nullptr) continue;                                                                        \
                logger::logStr(labels[elemI], -(int)strlen(labels[elemI]));                                                     \
        }                                                                                                                        \
        strFParser::freeCalloc();                                                                                                 \
        logger::endBlock();                                                                                                        \
    }
    LOGGER_LOGFIELDARRAY_IMPL1(int, d);

    void addBlock() {
        assert(logTarget != nullptr);
        addInvisibleBlock();
        logLine("{");
    }

    void endBlock() {
        assert(logTarget != nullptr);
        logLine("}");
        endInvisibleBlock();
    }

    void addInvisibleBlock() {
        ++marginCounter;
    }

    void endInvisibleBlock() {
        --marginCounter;
    }

    void logStr(const char* const str, int shiftW, int shiftH, int shiftHB) {
        assert(str != nullptr);
        assert(logTarget != nullptr);
        printLog(logTarget, htmlStrTemplate,
            marginCounter * 4 + shiftW, shiftH, str, shiftHB);
    }

    void logStr(const char* const str, int shiftW) {
        assert(str != nullptr);
        assert(logTarget != nullptr);
        logStr(str, shiftW, 0, 0);
    }

    void logStr(const char* const str, int shiftW, int shiftH) {
        assert(str != nullptr);
        assert(logTarget != nullptr);
        logStr(str, shiftW, shiftH, -shiftH);
    }

    void logLine(const char* const str) {
        assert(str != nullptr);
        assert(logTarget != nullptr);
        logStr(str, 0, 1, 0);
    }

    void logLine(const char* const str, int shiftW, int shiftH) {
        assert(str != nullptr);
        assert(logTarget != nullptr);
        logStr(str, shiftW, shiftH + 1, -shiftH);
    }
}
