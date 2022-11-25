#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

#include <strFParser.h>

#include "graphviz\graphvizTreeIncludeConsts.h"

#include "graphviz\graphvizTree.h"

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

    void logElem(size_t const elemIndex, void const* const elemPtr, void const* const nextPtr, void const* const prevPtr,
        ValueOutFunction_t const outFunc, size_t const bufN, void const* const valuePtr) {

        assert(logTarget != nullptr);

#define PRINTLOG_GRAPH_ELEM_BODY(NPtoken, ...) \
printLog(logTarget, GRAPH_ELEM_BODY(NPtoken, elemPtr, elemIndex, elemPtr, outFunc(bufN, valuePtr) __VA_OPT__(, __VA_ARGS__)))

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

        if (nextPtr)
            printLog(logTarget, GRAPH_ELEM_ORDER(elemPtr, nextPtr));
        if (nextPtr)
            printLog(logTarget, GRAPH_ARROW_2NEXT(elemPtr, nextPtr));
        if (prevPtr)
            printLog(logTarget, GRAPH_ARROW_2PREV(elemPtr, prevPtr));
    }

    void logNode(void const* const elemPtr, void const* const leftPtr, void const* const rightPtr,
        ValueOutFunction_t const outFunc, size_t const bufN, void const* const valuePtr) {

        assert(logTarget != nullptr);

#define PRINTLOG_GRAPH_NODE_BODY(NPtoken, ...) \
printLog(logTarget, GRAPH_NODE_BODY(NPtoken, elemPtr, elemPtr, outFunc(bufN, valuePtr) __VA_OPT__(, __VA_ARGS__)))

        if (leftPtr) {
            if (rightPtr) {
                PRINTLOG_GRAPH_NODE_BODY(PP, leftPtr, rightPtr);
            } else {
                PRINTLOG_GRAPH_NODE_BODY(PN, leftPtr);
            }
        } else {
            if (rightPtr) {
                PRINTLOG_GRAPH_NODE_BODY(NP, rightPtr);
            } else {
                PRINTLOG_GRAPH_NODE_BODY(NN);
            }
        }

#undef PRINTLOG_GRAPH_ELEM_BODY

        if (leftPtr)
            printLog(logTarget, GRAPH_ARROW_2LEFT(elemPtr, leftPtr));
        if (rightPtr)
            printLog(logTarget, GRAPH_ARROW_2RIGHT(elemPtr, rightPtr));
        if (leftPtr && rightPtr)
            printLog(logTarget, GRAPH_ELEM_ORDER_SIBLINGS(leftPtr, rightPtr));
    }

    void logHeadTailEgg(void const* const headPtr, void const* const tailPtr) {
        assert(logTarget != nullptr);

        printLog(logTarget, GRAPH_HEADTAIL_EGG(headPtr, tailPtr));
    }
}
