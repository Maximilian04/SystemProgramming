#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "logger.h"

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
        //assert(logTarget == nullptr);
        if (logTarget != nullptr) {
            return 2;
        }

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

        logger::logLine(strFParser::parseFCalloc("%s at %s (%d line)", funcName, fileName, lineN));
    }

    void logStructHead(const char* structName, const void* objPtr) {
        assert(structName != nullptr);

        logger::logLine(strFParser::parseFCalloc("%s[" COLORED_TEXT("cyan", "%p") "]:",
            structName, objPtr));
    }

    void logStructHeadDebug(const char* structName, const void* objPtr, const DebugInfo* debugPtr) {
        assert(structName != nullptr);

        logger::logLine(strFParser::parseFCalloc("%s[" COLORED_TEXT("cyan", "%p") "] "
            "\"%s\" at %s at %s (%d line):",
            structName, objPtr,
            debugPtr->objName, debugPtr->ctorCallFunc, debugPtr->ctorCallFile, debugPtr->ctorCallLine));
    }

    void logField(const char* fieldName, const char* valueStr, int shift) {
        assert(fieldName != nullptr);
        assert(valueStr != nullptr);

        logger::logLine(fieldName);

        logger::logStr(valueStr, (int)strlen(fieldName) + 1 + shift);

        strFParser::freeCalloc();
    }

    void logFieldArray(const char* fieldName, void* arrayPtr, size_t size, size_t elemSize,
        const char* (*outFunc)(void* elemPtr, size_t parseBufferNum, int digitNumber), const char** labels) {

        assert(fieldName != nullptr);
        assert(arrayPtr != nullptr);
        assert(outFunc != nullptr);

        logger::logLine(fieldName);
        logger::addBlock();
        int digitsNumber = numberOfDigits(size - 1);
        size_t parseBufferNum =/**/strFParser::addCallocBuf();
        size_t parseBufferNumAdd = strFParser::addCallocBuf();

        uint8_t* elemPtr = (uint8_t*)arrayPtr;
        for (size_t elemI = 0; elemI < size; ++elemI, elemPtr += elemSize) {
            logger::logLine(strFParser::parseFNBuf(parseBufferNumAdd,
                strFParser::parseFNBuf(parseBufferNum, "[%%%dd]", digitsNumber), elemI));

            outFunc(elemPtr, parseBufferNum, digitsNumber);

            if (labels == nullptr || labels[elemI] == nullptr) continue;
            logger::logStr(labels[elemI], -(int)strlen(labels[elemI]));
        }

        strFParser::freeCalloc();
        logger::endBlock();
    }

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

    void emergencyLog(const char* const str) {
        assert(str != nullptr);
        logger::openLogFile();
        logger::logHtmlHead();
        logger::printLog(logTarget, htmlEmergencyColorStart);
        logger::logLine(str);
        logger::printLog(logTarget, htmlEmergencyColorStop);
        logger::logHtmlTail();
        logger::closeLogFile();
    }

    void logMsg(const char* const str) {
        assert(str != nullptr);
        logger::openLogFile();
        logger::logHtmlHead();
        logger::logLine(str);
        logger::logHtmlTail();
        logger::closeLogFile();
    }

    void logImg(const char* const file) {
        assert(file != nullptr);
        logger::printLog(logTarget, htmlImageHead);
        logger::printLog(logTarget, file);
        logger::printLog(logTarget, htmlImageTail);
    }
}
