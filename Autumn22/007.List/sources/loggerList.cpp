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
        ListIterator elem;
        List::begin(list, &elem);
        do {
            size_t bufN = strFParser::addCallocBuf();
            logger::logField(">", strFParser::parseFNBuf(bufN, htmlCyanPointer, ListIterator::getValue(&elem)));
        } while (!ListIterator::next(&elem));
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
