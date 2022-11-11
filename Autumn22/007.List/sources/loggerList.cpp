#include <logger.h>
#include <graphviz.h>

#include "loggerList.h"

static void logGraphList(const List* const list);

void logList(const List* const list) {
    logger::addBlock();

    logger__logField(list, head, p, nullptr);
    logger__logField(list, tail, p, nullptr);
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
            char const* ptrStr = strFParser::parseFNBuf(bufN1, htmlCyanPointer, ListIterator::getValue(&elem));
            char const* valueStr = list->outFunc(bufN2, ListIterator::getValue(&elem));
            logger::logLine(strFParser::parseFNBuf(bufN3, "[%s] > %s", ptrStr, valueStr));

        } while (!ListIterator::next(&elem));

        strFParser::freeCalloc();
    }

    logger::endBlock();

    logger::endBlock();

    logGraphList(list);
}

#define LOG_GRAPH_FILE_NAME_TEMPLATE "stuff/log_list_graph_%d.gv"

static void logGraphList(const List* const list) {
    static int logToken = 0;
    ++logToken;
    size_t bufN = strFParser::addCallocBuf();
    if (graphviz::openLogFile(strFParser::parseFNBuf(bufN, LOG_GRAPH_FILE_NAME_TEMPLATE, logToken))) {
        printf("Cannot create graphviz file\n");
        return;
    }

    graphviz::logGraphHead();

    if (!List::isEmpty(list)) {
        ListIterator elem;
        List::begin(list, &elem);
        do {
            graphviz::logElem(ListIterator::getElemPtr(&elem), ListIterator::getNextPtr(&elem), ListIterator::getPrevPtr(&elem),
                List::getOutFunc(list), bufN, ListIterator::getValue(&elem));
        } while (!ListIterator::next(&elem));

    }

    graphviz::logGraphTail();

    graphviz::closeLogFile();
    strFParser::freeCalloc();
}
