#include <stdlib.h>

#include <logger.h>
#include <graphviz.h>

#include "loggerList.h"

static void logGraphList(const List* const list);

void logList(const List* const list) {
    logger::addBlock();

    logger__logField(list, freeTail, u, 0);
    logger__logField(list, size, u, SIZE_MAX, 4);
    logger__logField(list, capacity, u, SIZE_MAX);

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
            char const* ptrStr = strFParser::parseFNBuf(bufN1, htmlLogicalPointer, ListIterator::getElemPtr(list, &elem));
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

    if (list->bufferElem)
        graphviz::logElem(0, 0, list->bufferElem->next,
            list->bufferElem->prev, List::getOutFunc(list), bufN, list->bufferValue, 0);

    if (list->capacity) {
        struct ElemInfo {
            bool isUsed;
            size_t logicIndex;
        };

        ElemInfo* logicInfo = (ElemInfo*)calloc(list->capacity + 1, sizeof(ElemInfo));
        for (size_t i = 0; i <= list->capacity; ++i) {
            logicInfo[i].isUsed = false;
            logicInfo[i].logicIndex = 0;
        }

        ListIterator elem;
        List::begin(list, &elem);
        size_t elemIndex = 0;
        if (!List::isEmpty(list)) {
            do {
                logicInfo[ListIterator::getElemPtr(list, &elem)].isUsed = true;
                logicInfo[ListIterator::getElemPtr(list, &elem)].logicIndex = elemIndex++;
            } while (!ListIterator::next(list, &elem));
        }

        for (elemIndex = 1; elemIndex <= list->capacity; ++elemIndex) {
            elem.ptr = elemIndex;
            if (logicInfo[elemIndex].isUsed);
            graphviz::logElem(logicInfo[elemIndex].logicIndex, ListIterator::getElemPtr(list, &elem), ListIterator::getNextPtr(list, &elem),
                ListIterator::getPrevPtr(list, &elem), List::getOutFunc(list), bufN, ListIterator::getValue(list, &elem), elemIndex - 1);
        }
        /*do {
            graphviz::logElem(elemIndex++, ListIterator::getElemPtr(list, &elem), ListIterator::getNextPtr(list, &elem),
                ListIterator::getPrevPtr(list, &elem), List::getOutFunc(list), bufN, ListIterator::getValue(list, &elem));
        } while (!ListIterator::next(list, &elem));*/

        graphviz::logHeadTailEgg(list->bufferElem->prev, list->bufferElem->next, list->freeTail);

        free(logicInfo);
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
