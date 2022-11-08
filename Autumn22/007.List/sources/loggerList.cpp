#include <logger.h>

#include "loggerList.h"

void logList(const List* const list) {
    logger::addBlock();
    // logger__logField(list, size, size_t, 4);
    // logger__logField(stack, capacity, size_t);
    logger__logField(list, head, p, nullptr);

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
    free(labels);

    logger::endBlock();*/
}
