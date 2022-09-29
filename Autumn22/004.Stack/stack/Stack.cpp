#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\logger\loggerStack.h" //TODO: WTF???
#include "..\strFParser\strFParser.h"

#include "Stack.h"

namespace stack {
    /**
     * @brief Stack constructor
     *
     * @param [out] stack Stack
     * @param [in] capacity Init capacity
     * @return Error Error code
     */
#ifdef STACK_DEBUG
    Error ctor(Stack* const stack, DEBUGINFO_CTOR_ARGS_H, size_t capacity) {
#else // !STACK_DEBUG
    Error ctor(Stack* const stack, size_t capacity) {
#endif // STACK_DEBUG
        assert(stack != nullptr);

        stack->size = 0;
        stack->capacity = capacity;
        stack->data = nullptr;
        if (capacity > 0) {
            stack->data = (Elem_t*)calloc(capacity, sizeof(Elem_t));
            assert(stack->data != nullptr);
        }

#ifdef STACK_DEBUG
        stack->debugInfo.objName = objName;
        stack->debugInfo.ctorCallLine = ctorCallLine;
        stack->debugInfo.ctorCallFile = ctorCallFile;
        stack->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // STACK_DEBUG

        return Error::OK;
    }

    /**
     * @brief Stack destructor
     *
     * @param [out] stack Stack
     * @return Error Error code
     */
    Error dtor(Stack* const stack) {
        free(stack->data);

        return Error::OK;
    }

    /**
     * @brief Change stack buffer size
     *
     * @param [out] stack Stack
     * @param [in] newCapacity New buffer size
     * @return Error Error code
     */
    Error resize(Stack* const stack, size_t newCapacity) {
        assert(stack != nullptr);

        if (newCapacity == 0) {
            free(stack->data);
            stack->data = nullptr;
        } else {
            stack->data = (Elem_t*)realloc(stack->data, newCapacity * sizeof(Elem_t));
            assert(stack->data != nullptr);
        }
        if (newCapacity > stack->capacity) {
            memset((Elem_t*)(stack->data) + stack->size, 0, (newCapacity - stack->size) * sizeof(Elem_t));
        }
        stack->capacity = newCapacity;

        if (newCapacity < stack->size) {
            stack->size = newCapacity;
            return Error::DATA_TRUNC;
        }
        return Error::OK;
    }

    /**
     * @brief Push element to stack
     *
     * @param [out] stack Stack
     * @param [in] elem Element
     * @return Error Error code
     */
    Error push(Stack* const stack, Elem_t elem) {
        assert(stack != nullptr);
        assert(stack->size < stack->capacity);
        stack->data[stack->size] = elem;
        stack->size++;

        return Error::OK;
    }

    /**
     * @brief Get the last element to *dst* and erase it from stack
     *
     * @param [out] stack Stack
     * @param [out] dst Pointer to variable to set
     * @return Error Error code
     */
    Error pop(Stack* const stack, Elem_t* const dst) {
        assert(stack != nullptr);

        if (dst != nullptr) {
            getLast(stack, dst);
        }
        stack->size--;
        return Error::OK;
    }

    /**
     * @brief Get the last element from stack to *dst*
     *
     * @param [out] stack Stack
     * @param [out] dst Pointer to variable to set
     * @return Error Error code
     */
    Error getLast(Stack* const stack, Elem_t* const dst) {
        assert(stack != nullptr);
        assert(dst != nullptr);

        if (stack->size == 0) {
            return Error::EMPTY;
        }
        *dst = stack->data[stack->size - 1];
        return Error::OK;
    }

    /**
     * @brief Dump Stack info
     *
     * @param [in] stack Stack
     * @return Error Error code
     */
    Error dump(Stack* const stack, LOGFUNCHEAD_ARGS_H) {
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

        return Error::OK;
    }
}
