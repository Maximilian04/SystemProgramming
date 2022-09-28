#include <assert.h>
#include <stdio.h>

#include "..\logger\loggerStack.h" //TODO: WTF???

#include "Stack.h"

namespace stack {
    /**
     * @brief Stack constructor
     *
     * @param [out] stack Stack
     * @param [in] capacity Init capacity
     */
    void ctor(Stack* stack, size_t capacity) {

        stack->size = 0;
        stack->capacity = capacity;
        stack->data = (Elem_t*)calloc(capacity, sizeof(Elem_t));
        assert(stack->data != nullptr);
    }

    /**
     * @brief Stack destructor
     *
     * @param [out] stack Stack
     */
    void dtor(Stack* stack) {
        free(stack->data);
    }

    /**
     * @brief Push element to stack
     *
     * @param [in] stack Stack
     * @param [in] elem Element
     */
    void push(Stack* stack, Elem_t elem) {

        assert(stack->size < stack->capacity);
        stack->data[stack->size] = elem;
        stack->size++;
    }

    /**
     * @brief Dump Stack info
     *
     * @param [in] stack Stack
     */
    void dump(Stack* stack, LOGFUNCHEAD_ARGS_H) {
        logger::openLogFile();

        logger::logHtmlHead();
        logger__logFuncHead());
        //logger::logFuncHead(LOGFUNCHEAD_ARGS);
        logger::logStructHead("Stack", stack);
        logger::logStack(stack);
        logger::logHtmlTail();

        logger::closeLogFile();
    }
}
