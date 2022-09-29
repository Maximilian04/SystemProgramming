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
#ifdef STACK_DEBUG
    void ctor(Stack* stack, DEBUGINFO_CTOR_ARGS_H, size_t capacity) {
#else // !STACK_DEBUG
    void ctor(Stack* stack, size_t capacity) {
#endif // STACK_DEBUG

        stack->size = 0;
        stack->capacity = capacity;
        stack->data = (Elem_t*)calloc(capacity, sizeof(Elem_t));
        assert(stack->data != nullptr);

#ifdef STACK_DEBUG
        stack->debugInfo.objName = objName;
        stack->debugInfo.ctorCallLine = ctorCallLine;
        stack->debugInfo.ctorCallFile = ctorCallFile;
        stack->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // STACK_DEBUG
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
#ifdef STACK_DEBUG
        logger::logStructHeadDebug("Stack", stack);
#else // !STACK_DEBUG
        logger::logStructHead("Stack", stack);
#endif // STACK_DEBUG
        logger::logStack(stack);
        logger::logHtmlTail();

        logger::closeLogFile();
    }
}
