#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\logger\loggerStack.h" //TODO: WTF???
#include "..\strFParser\strFParser.h"

#include "Stack.h"

namespace stack {
    static const int POISON = 0xCAFED00D;

    double getCapacityFactor(size_t currentCapacity);
    Error increaseSize(Stack* const stack);
    Error decreaseSize(Stack* const stack);

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
        stack->data = nullptr;
        if (capacity > 0)
            resize(stack, capacity);

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
     * @brief Get size
     *
     * @param [in] stack
     * @return size_t Size
     */
    size_t getSize(Stack* const stack) {
        assert(stack != nullptr);
        return stack->size;
    }

    /**
     * @brief Get capacity factor depending on current capacity
     *
     * @param [in] currentCapacity Current capacity
     * @return double Factor
     */
    double getCapacityFactor(size_t currentCapacity) {
        if (currentCapacity == 0)
            return 1.0;
        return 2.0;
    }

    /**
     * @brief Increase stack size
     *
     * @param [out] stack Stack
     * @return Error Error code
     */
    Error increaseSize(Stack* const stack) {
        assert(stack != nullptr);
        if (stack->size == stack->capacity) {
            size_t newCapacity = (size_t)(getCapacityFactor(stack->capacity) * double(stack->capacity));
            newCapacity = newCapacity + (newCapacity > stack->capacity ? 0 : 1);

            Error err = resize(stack, newCapacity);
            if (err) return err;
        }

        stack->size++;

        return Error::OK;
    }

    Error decreaseSize(Stack* const stack) {
        assert(stack != nullptr);
        if (stack->size == 0)
            return Error::EMPTY;

        stack->size--;

        size_t capacityBound = (size_t)(getCapacityFactor(stack->size) * double(stack->size));
        assert(capacityBound >= stack->size);
        if (capacityBound < stack->capacity) {
            Error err = resize(stack, stack->size);
            if (err) return err;
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

        Error err = increaseSize(stack);
        if (err) return err;

        stack->data[stack->size - 1] = elem;

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
            Error err = getLast(stack, dst);
            if (err) return err;
        }
        Error err = decreaseSize(stack);
        if (err) return err;

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
