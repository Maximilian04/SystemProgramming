#include <logger.h>

#include "loggerList.h"

void logList(const List* const list) {
    logger::addBlock();
    // logger__logField(list, size, size_t, 4);
    // logger__logField(stack, capacity, size_t);
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

            // logger::logStr(strFParser::parseFNBuf(bufN, "", ListIterator::getValue(&elem)), 0);

            // logger::logField(">", strFParser::parseFNBuf(bufN, htmlCyanPointer, ListIterator::getValue(&elem)), -1);
        } while (!ListIterator::next(&elem));

        strFParser::freeCalloc();
    }
    logger::endBlock();
    /*if (stack->data == nullptr) {
        logger__logField(stack, data, Elem_tPTR));

        return;
    }
    const char* starPtr = "*";
    const char** labels = (const char**)calloc(stack->capacity, sizeof(const char*));
    for (size_t labelI = 0; labelI < stack->capacity; ++labelI) {
        labels[labelI] = labelI < stack->size ? nullptr : starPtr;
    }
    logger__logFieldArray(stack, data, stack->capacity, Elem_t), labels);
    free(labels);*/

    logger::endBlock();
}
