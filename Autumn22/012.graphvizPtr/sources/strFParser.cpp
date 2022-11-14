#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "strFParser.h"

namespace strFParser {
    const char* vparseFBuf(char* buffer, const char* format, va_list ap);

    static char** callocList = nullptr;
    static size_t callocListSize = 0;

    const char* parseFCalloc(const char* format, ...) {
        assert(format != nullptr);

        size_t bufferNum = addCallocBuf();
        assert(bufferNum < callocListSize);

        va_list ap;
        va_start(ap, format);
        vparseFBuf(callocList[bufferNum], format, ap);
        va_end(ap);

        return callocList[bufferNum];
    }

    const char* parseFNBuf(size_t bufferNum, const char* format, ...) {
        assert(format != nullptr);
        assert(callocList != nullptr);
        assert(callocListSize > 0);
        assert(bufferNum < callocListSize);

        va_list ap;
        va_start(ap, format);
        vparseFBuf(callocList[bufferNum], format, ap);
        va_end(ap);

        return callocList[bufferNum];
    }

    size_t addCallocBuf() {
        char* buffer = (char*)calloc(LINE_BUFFER_SIZE, sizeof(char));

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
        for (size_t listI = 0; listI < callocListSize; ++listI) {
            assert(callocList[listI] != nullptr);
            free(callocList[listI]);
        }

        if (callocListSize) {
            assert(callocList);

            free(callocList);
            callocList = nullptr;
            callocListSize = 0;
        }
        assert(!callocList);
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
