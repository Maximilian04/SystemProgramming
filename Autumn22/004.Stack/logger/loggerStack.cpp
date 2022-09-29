#include "loggerStack.h"

#include "..\logger\logger.h"

namespace logger {
    void logStackData(const Stack* const stack);

    void logStackData(const Stack* const stack) {
        if (stack->data == nullptr) {
            logger__logField(stack, data));
            
            return;
        }
        const char* starPtr = "*";
        const char** labels = (const char**)calloc(stack->capacity, sizeof(const char*));
        for (size_t labelI = 0; labelI < stack->capacity; ++labelI) {
            labels[labelI] = labelI < stack->size ? nullptr : starPtr;
        }
        logger__logFieldArray(stack, data, stack->capacity), labels);
        free(labels);
    }

    void logStack(const Stack* const stack) {
        logger::addBlock();
        logger__logField(stack, size), 4);
        logger__logField(stack, capacity));
        logStackData(stack);
        logger::endBlock();
    }
}
