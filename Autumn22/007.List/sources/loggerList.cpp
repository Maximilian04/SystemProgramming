#include <logger.h>

#include "loggerList.h"

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
}
