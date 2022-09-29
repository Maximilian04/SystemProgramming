#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\logger\loggerStack.h" //TODO: WTF???
#include "..\strFParser\strFParser.h"

#include "Stack.h"

#define VERIFY(obj) if (verify(obj)) STACK__dump(*obj))
#define VERIFYINLINE(obj) (verify(obj) ? STACK__dump(*obj)) : 0)

namespace stack {
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

        VERIFY(stack);
        return Error::OK;
    }

    /**
     * @brief Stack destructor
     *
     * @param [out] stack Stack
     * @return Error Error code
     */
    Error dtor(Stack* const stack) {
        VERIFY(stack);
        free(stack->data);

        stack->data = stack_POISON_PTR(Elem_t);
        stack->size = stack_POISON(size_t);
        stack->capacity = stack_POISON(size_t);

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
        VERIFY(stack);

        if (newCapacity == 0) {
            free(stack->data);
            stack->data = nullptr;
        } else {
            stack->data = (Elem_t*)realloc(stack->data, newCapacity * sizeof(Elem_t));
            assert(stack->data != nullptr);
        }
        if (newCapacity > stack->capacity) {
            memset((Elem_t*)(stack->data) + stack->capacity, 0, (newCapacity - stack->capacity) * sizeof(Elem_t));

            for (size_t elemI = stack->capacity; elemI < newCapacity; ++elemI) {
                stack->data[elemI] = stack_POISON(Elem_t);
            }
        }
        stack->capacity = newCapacity;

        if (newCapacity < stack->size) {
            stack->size = newCapacity;
            VERIFY(stack);
            return Error::DATA_TRUNC;
        }
        VERIFY(stack);
        return Error::OK;
    }

    /**
     * @brief Get size
     *
     * @param [in] stack
     * @return size_t Size
     */
    size_t getSize(Stack* const stack) {
        VERIFY(stack);
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
            if (err) return VERIFYINLINE(stack), err;
        }

        stack->size++;

        return Error::OK;
    }

    Error decreaseSize(Stack* const stack) {
        assert(stack != nullptr);
        if (stack->size == 0)
            return Error::EMPTY;

        stack->data[stack->size - 1] = stack_POISON(Elem_t);
        stack->size--;

        size_t capacityBound = (size_t)(getCapacityFactor(stack->size) * double(stack->size));
        assert(capacityBound >= stack->size);
        if (capacityBound < stack->capacity) {
            Error err = resize(stack, stack->size);
            if (err) return VERIFYINLINE(stack), err;
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
        VERIFY(stack);

        Error err = increaseSize(stack);
        if (err) return err;

        stack->data[stack->size - 1] = elem;

        VERIFY(stack);
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
        VERIFY(stack);

        if (dst != nullptr) {
            Error err = getLast(stack, dst);
            if (err) return VERIFYINLINE(stack), err;
        }
        Error err = decreaseSize(stack);
        if (err) return VERIFYINLINE(stack), err;

        VERIFY(stack);
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
        VERIFY(stack);
        assert(dst != nullptr);

        if (stack->size == 0) {
            VERIFY(stack);
            return Error::EMPTY;
        }
        *dst = stack->data[stack->size - 1];
        VERIFY(stack);
        return Error::OK;
    }

    /**
     * @brief Dump Stack info
     *
     * @param [in] stack Stack
     * @return Error Error code
     */
    Error dump(Stack* const stack, LOGFUNCHEAD_ARGS_H) {
        assert(stack != nullptr);
        assert(funcName != nullptr);
        assert(fileName != nullptr);
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

    /**
     * @brief Verify correctness of Stack
     *
     * @param [in] stack Stack
     * @return Error Error code as disjunction of StackVerifierError
     */
    VerifierCode verify(Stack* const stack) {
        assert(stack != nullptr);
        VerifierCode errorCode = StackVerifierError::OK;

        if (stack->size > stack->capacity) {
            errorCode |= StackVerifierError::SIZE_OVER_CAP;
            logger::emergencyLog(strFParser::parseF("Stack size[%d] > than capacity[%d]!", stack->size, stack->capacity));
        }
        if (stack->capacity == 0) {
            if (stack->data != nullptr) {
                errorCode |= StackVerifierError::BAD_DATA_PTR;
                logger::emergencyLog(strFParser::parseF("Stack data field[%p] isn't nullptr with zero capacity[%d]!",
                    stack->data, stack->capacity));
            }
        } else { // stack->capacity != 0
            if (stack->data == nullptr) {
                errorCode |= StackVerifierError::BAD_DATA_PTR;
                logger::emergencyLog(strFParser::parseF("Stack data field[%p] is nullptr with unzero capacity[%d]!",
                    stack->data, stack->capacity));
            }
        }

        if (errorCode) return errorCode;

        for (size_t elemI = 0; elemI < stack->capacity; ++elemI) {
            if (elemI < stack->size) {
                if (stack->data[elemI] == stack_POISON(Elem_t)) {
                    errorCode |= StackVerifierError::POISONE_LEAK;
                    logger::emergencyLog(strFParser::parseF("Stack poison in data space[%p]: index[%d] poisoned!",
                        &stack->data[elemI], elemI));
                }
            } else { // elemI >= stack->size
                if (stack->data[elemI] != stack_POISON(Elem_t)) {
                    errorCode |= StackVerifierError::POISONE_LEAK;
                    logger::emergencyLog(strFParser::parseF("Stack (approximately) data in poisoned space[%p]: index[%d]: data (%d)!",
                        &stack->data[elemI], elemI, stack->data[elemI])); //TODO change %d for data to universal flag
                }
            }
        }

        return errorCode;
    }
}
