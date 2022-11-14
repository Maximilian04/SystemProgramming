#include <logger.h>
#include <graphviz.h>

#include "loggerList.h"

static void logGraphList(const List* const list);

void logList(const List* const list) {
    logger::addBlock();

    // logger__logField(list, head, p, nullptr);
    // logger__logField(list, tail, p, nullptr);
    logger__logField(list, freeTail, u, 0);
    logger__logField(list, size, u, 0, 4);
    logger__logField(list, capacity, u, 0);

    logger__logField(list, bufferElem, p, nullptr, 1);
    logger__logField(list, bufferValue, p, nullptr);
    logger__logField(list, elemSize, u, 0);

    logger::logLine("Elements: ");
    logger::addBlock();

    if (!List::isEmpty(list)) {
        size_t bufN1 = strFParser::addCallocBuf();
        size_t bufN2 = strFParser::addCallocBuf();
        size_t bufN3 = strFParser::addCallocBuf();

        ListIterator elem;
        List::begin(list, &elem);
        do {
            char const* ptrStr = strFParser::parseFNBuf(bufN1, htmlCyanPointer, ListIterator::getValue(list, &elem));
            char const* valueStr = list->outFunc(bufN2, ListIterator::getValue(list, &elem));
            logger::logLine(strFParser::parseFNBuf(bufN3, "[%s] > %s", ptrStr, valueStr));

        } while (!ListIterator::next(list, &elem));

        strFParser::freeCalloc();
    }

    logger::endBlock();

    logger::endBlock();

    logGraphList(list);
}

#define LOG_GRAPH_FILENAME_TEMPLATE "stuff/log_list_graph_%d.gv"
#define LOG_GRAPH_IMG_FILENAME_TEMPLATE "stuff/log_list_graph_%d.png"
#define LOG_FILENAME     strFParser::parseFNBuf(bufN1, LOG_GRAPH_FILENAME_TEMPLATE, logToken)
#define LOG_IMG_FILENAME strFParser::parseFNBuf(bufN2, LOG_GRAPH_IMG_FILENAME_TEMPLATE, logToken)

static void logGraphList(const List* const list) {
    static int logToken = 0;
    ++logToken;
    size_t bufN  = strFParser::addCallocBuf();
    size_t bufN1 = strFParser::addCallocBuf();
    size_t bufN2 = strFParser::addCallocBuf();
    if (graphviz::openLogFile(LOG_FILENAME)) {
        printf("Cannot create graphviz file\n");
        return;
    }

    graphviz::logGraphHead();

    if (!List::isEmpty(list)) {
        ListIterator elem;
        List::begin(list, &elem);
        size_t elemIndex = 0;
        do {
            // graphviz::logElem(elemIndex++, ListIterator::getElemPtr(list, &elem), ListIterator::getNextPtr(list, &elem),
                // ListIterator::getPrevPtr(list, &elem), List::getOutFunc(list), bufN, ListIterator::getValue(list, &elem));
        } while (!ListIterator::next(list, &elem));

        // graphviz::logHeadTailEgg(list->head, list->tail);
    }

    graphviz::logGraphTail();

    graphviz::closeLogFile();

    graphviz::run(bufN, LOG_FILENAME, LOG_IMG_FILENAME);
    logger::logImg(LOG_IMG_FILENAME);

    strFParser::freeCalloc();
}

#undef LOG_GRAPH_FILENAME_TEMPLATE
#undef LOG_GRAPH_IMG_FILENAME_TEMPLATE
#undef LOG_FILENAME
#undef LOG_IMG_FILENAME
