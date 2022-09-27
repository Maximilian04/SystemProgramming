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

    const char* parseFCalloc(const char* format, ...) {
        char* buffer = (char*)calloc(LINE_BUFFER_SIZE, sizeof(char));

        va_list ap;
        va_start(ap, format);
        vparseFBuf(buffer, format, ap);
        va_end(ap);
        return buffer;
    }

    const char* vparseFBuf(char* buffer, const char* format, va_list ap) {
        assert(buffer != nullptr);
        assert(format != nullptr);

        int lineSize = vsnprintf(buffer, LINE_BUFFER_SIZE, format, ap);
        assert(lineSize < LINE_BUFFER_SIZE);

        return buffer;
    }
}
