#include "loggerStack.h"

#include "..\logger\logger.h"

namespace logger {
    void logStackData(const Stack* const stack);

    void logStackData(const Stack* const stack) {
        if (stack->data == nullptr) {
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
    }

    void logStack(const Stack* const stack) {
        logger::addBlock();
        logger__logField(stack, size, size_t), 4);
        logger__logField(stack, capacity, size_t));
        logStackData(stack);
        logger::endBlock();
    }
}
