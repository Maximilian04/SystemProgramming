#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "strFParser.h"

namespace strFParser {
    const char* vparseFBuf(char* buffer, const char* format, va_list ap);

    const char* parseF(const char* format, ...) {
        static char buffer[LINE_BUFFER_SIZE] = { 0 };

        va_list ap;
        va_start(ap, format);
        vparseFBuf(buffer, format, ap);
        va_end(ap);
        return buffer;
    }

    static char** callocList = nullptr;
    static int callocListSize = 0;
    const char* parseFCalloc(const char* format, ...) {
        assert(format != nullptr);

        int bufferNum = addCallocBuf();
        assert(bufferNum >= 0);
        assert(bufferNum < callocListSize);

        va_list ap;
        va_start(ap, format);
        vparseFBuf(callocList[bufferNum], format, ap);
        va_end(ap);

        return callocList[bufferNum];
    }

    const char* parseFNBuf(int bufferNum, const char* format, ...) {
        assert(format != nullptr);
        assert(callocList != nullptr);
        assert(bufferNum >= 0);
        assert(callocListSize > 0);
        assert(bufferNum < callocListSize);

        va_list ap;
        va_start(ap, format);
        vparseFBuf(callocList[bufferNum], format, ap);
        va_end(ap);

        return callocList[bufferNum];
    }

    int addCallocBuf() {
        char* buffer = (char*)calloc(LINE_BUFFER_SIZE, sizeof(char));

        assert(callocListSize >= 0);
        ++callocListSize;
        if (callocListSize == 1) {
            assert(callocList == nullptr);
            callocList = (char**)calloc(1, sizeof(char*));
        } else {
            assert(callocList != nullptr);
            callocList = (char**)realloc(callocList, sizeof(char*) * callocListSize);
        }
        assert(callocList != nullptr);
        callocList[callocListSize - 1] = buffer;

        return callocListSize - 1;
    }

    void freeCalloc() {
        for (int listI = 0; listI < callocListSize; ++listI) {
            assert(callocList[listI] != nullptr);
            free(callocList[listI]);
        }

        free(callocList);
        callocList = nullptr;
        callocListSize = 0;
    }

    const char* vparseFBuf(char* buffer, const char* format, va_list ap) {
        assert(buffer != nullptr);
        assert(format != nullptr);

        int lineSize = vsnprintf(buffer, LINE_BUFFER_SIZE, format, ap);
        assert(lineSize < LINE_BUFFER_SIZE);
#ifdef NDEBUG
        lineSize = lineSize;
#endif

        return buffer;
    }
}
