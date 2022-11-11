#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

#include "graphvizIncludeConsts.h"

#include "graphviz.h"

namespace graphviz {
    static FILE* logTarget = nullptr;

    static void printLog(FILE* stream, const wchar_t* format, ...);

    Error openLogFile(const char* fileName) {
        assert(fileName != nullptr);
        assert(logTarget == nullptr);
        if (logTarget != nullptr) {
            // return;
        }

        FILE* file = 0;
        file = fopen(fileName, "wt, ccs=UTF-8");
        if (file == nullptr)
            return Error::OPEN_FILE_ERR;

        setvbuf(file, nullptr, _IONBF, 0);
        logTarget = file;

        return Error::OK;
    }

    Error closeLogFile() {
        assert(logTarget != nullptr && logTarget != stdout);

        int fcloseRes = fclose(logTarget);
        logTarget = nullptr;

        return fcloseRes ? Error::CLOSE_FILE_ERR : Error::OK;
    }

    static void printLog(FILE* stream, const wchar_t* format, ...) {
        assert(stream != nullptr);
        assert(format != nullptr);

        va_list ap;
        va_start(ap, format);
        vfwprintf(stream, format, ap);
        va_end(ap);
    }

    void logGraphHead() {
        assert(logTarget != nullptr);
        printLog(logTarget, L"%s", graphHead);
    }

    void logGraphTail() {
        assert(logTarget != nullptr);
        printLog(logTarget, L"%s", graphTail);
    }

    void logElem(void const* const elemPtr, void const* const nextPtr, void const* const prevPtr,
        ValueOutFunction_t const outFunc, size_t const bufN, void const* const valuePtr) {

        assert(logTarget != nullptr);
        printLog(logTarget, GRAPH_ELEM_BODY(elemPtr, nextPtr, prevPtr, elemPtr, outFunc(bufN, valuePtr)));
    }
}
