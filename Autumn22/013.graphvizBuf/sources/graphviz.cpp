#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <strFParser.h>

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

    Error run(size_t bufN, const char* fileGVName, const char* filePNGName) {
        assert(fileGVName != nullptr);
        assert(filePNGName != nullptr);
        assert(logTarget == nullptr && "Close file before processing");

        // printf("!'%s'\n", strFParser::parseFNBuf(bufN, graphRunCommandTemplate, fileGVName, filePNGName));
        return system(strFParser::parseFNBuf(bufN, graphRunCommandTemplate, fileGVName, filePNGName)) ?
            Error::GRAPHVIZ_ERR : Error::OK;
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

    void logElem(size_t const elemIndex, size_t const elemPtr, size_t const nextPtr, size_t const prevPtr,
        ValueOutFunction_t const outFunc, size_t const bufN, void const* const valuePtr, size_t const prevOrder) {

        assert(logTarget != nullptr);

#define PRINTLOG_GRAPH_ELEM_BODY(NPtoken, ...)                                                                                           \
if (elemPtr)                                                                                                                              \
    printLog(logTarget, GRAPH_ELEM_BODY(NPtoken, elemPtr, elemIndex, elemPtr, outFunc(bufN, valuePtr) __VA_OPT__(, __VA_ARGS__)));         \
else                                                                                                                                        \
    printLog(logTarget, GRAPH_ELEM_BODY(NPtoken##Managing, elemPtr, elemIndex, elemPtr, outFunc(bufN, valuePtr) __VA_OPT__(, __VA_ARGS__))); \

        if (nextPtr) {
            if (prevPtr) {
                PRINTLOG_GRAPH_ELEM_BODY(PP, nextPtr, prevPtr);
            } else {
                PRINTLOG_GRAPH_ELEM_BODY(PN, nextPtr);
            }
        } else {
            if (prevPtr) {
                PRINTLOG_GRAPH_ELEM_BODY(NP, prevPtr);
            } else {
                PRINTLOG_GRAPH_ELEM_BODY(NN);
            }
        }

#undef PRINTLOG_GRAPH_ELEM_BODY

        if (elemPtr)
            printLog(logTarget, GRAPH_ELEM_ORDER(prevOrder, elemPtr));
        if (nextPtr)
            printLog(logTarget, GRAPH_ARROW_2NEXT(elemPtr, nextPtr));
        if (prevPtr)
            printLog(logTarget, GRAPH_ARROW_2PREV(elemPtr, prevPtr));
    }

    void logHeadTailEgg(size_t const headPtr, size_t const tailPtr, size_t const freeTailPtr) {
        assert(logTarget != nullptr);

        printLog(logTarget, GRAPH_HEADTAIL_EGG(headPtr, tailPtr));
        printLog(logTarget, GRAPH_EGG(freeTailPtr, free));
    }
}
