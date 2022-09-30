#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>

#include "..\logger\loggerStack.h" //TODO: WTF???
#include "..\strFParser\strFParser.h"

#include "Stack.h"

#define VERIFY(obj) if (verify(obj)) STACK__dump(*obj))
#define VERIFYINLINE(obj) (verify(obj) ? STACK__dump(*obj)) : 0)

#ifdef STACK_CANARY
#define DATA_CANARY_BEGIN_PTR(data) ((data != nullptr) ? ((Canary_t*)(data) - 1) : nullptr)
#define DATA_CANARY_BEGIN_PTR_REVERSE(data)     (Elem_t*)((Canary_t*)(data) + 1)
#define DATA_CANARY_END_PTR(data, capacity)     (Canary_t*)((Elem_t*)(data) + (capacity))
#define DATA_SIZE (newCapacity * sizeof(Elem_t)) + (2 * sizeof(Canary_t))
#else // !STACK_CANARY
#define DATA_CANARY_BEGIN_PTR(data)        (data)
#define DATA_CANARY_BEGIN_PTR_REVERSE(data)(data)
#define DATA_SIZE (newCapacity * sizeof(Elem_t))
#endif // STACK_CANARY
#define VER_DATA_CANARY_BGN_PTR DATA_CANARY_BEGIN_PTR(stack->data)
#define VER_DATA_CANARY_END_PTR DATA_CANARY_END_PTR(stack->data, stack->capacity)


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
        stack->capacity = 0;

#ifdef STACK_DEBUG
        stack->debugInfo.objName = objName;
        stack->debugInfo.ctorCallLine = ctorCallLine;
        stack->debugInfo.ctorCallFile = ctorCallFile;
        stack->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // STACK_DEBUG

#ifdef STACK_CANARY
        stack->canaryBegin = stack_POISON(Canary_t);
        stack->canaryEnd   = stack_POISON(Canary_t);
#endif // STACK_CANARY

        if (capacity > 0)
            resize(stack, capacity);

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
        free(DATA_CANARY_BEGIN_PTR(stack->data));

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
            free(DATA_CANARY_BEGIN_PTR(stack->data));
            stack->data = nullptr;
        } else {
            stack->data = (Elem_t*)realloc(DATA_CANARY_BEGIN_PTR(stack->data), DATA_SIZE);
            stack->data = DATA_CANARY_BEGIN_PTR_REVERSE(stack->data);
            assert(stack->data != nullptr);

#ifdef STACK_CANARY
            *(DATA_CANARY_BEGIN_PTR(stack->data))              = stack_POISON_CANARY;
            *(DATA_CANARY_END_PTR  (stack->data, newCapacity)) = stack_POISON_CANARY;
#endif // STACK_CANARY
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
        if (stack == nullptr) {
            logger::emergencyLog("Stack is nullptr");
            return Error::NULLPTR_ERR;
        } else {
#ifdef STACK_DEBUG
            logger::logStructHeadDebug("Stack", stack, &stack->debugInfo);
#else // !STACK_DEBUG
            logger::logStructHead("Stack", stack);
#endif // STACK_DEBUG
            logger::logStack(stack);
        }
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
        if (stack == nullptr) {
            errorCode |= StackVerifierError::NULLPTR_ERR;
            logger::emergencyLog(strFParser::parseF("Stack pointer is nullptr[%p]!", stack));
        }

        if (errorCode) return errorCode;

#ifdef STACK_CANARY
        if (stack->canaryBegin != stack_POISON_CANARY) {
            errorCode |= StackVerifierError::CANARY_LEAK;
            logger::emergencyLog(strFParser::parseF("Canary protection-begin[%p] has leaked: (%" PRIx64 ") != (%" PRIx64 ")!",
                &stack->canaryBegin, stack->canaryBegin, stack_POISON_CANARY));
        }
        if (stack->canaryEnd != stack_POISON_CANARY) {
            errorCode |= StackVerifierError::CANARY_LEAK;
            logger::emergencyLog(strFParser::parseF("Canary protection---end[%p] has leaked: (%" PRIx64 ") != (%" PRIx64 ")!",
                &stack->canaryEnd, stack->canaryEnd, stack_POISON_CANARY));
        }
#endif // STACK_CANARY

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

#ifdef STACK_CANARY //TODO
            if (*VER_DATA_CANARY_BGN_PTR != stack_POISON_CANARY) {
                errorCode |= StackVerifierError::CANARY_LEAK;
                logger::emergencyLog(strFParser::parseF("Data canary protection-begin[%p] has leaked: (%" PRIx64 ") != (%" PRIx64 ")!",
                    VER_DATA_CANARY_BGN_PTR, *VER_DATA_CANARY_BGN_PTR, stack_POISON_CANARY));
            }
            if (*VER_DATA_CANARY_END_PTR != stack_POISON_CANARY) {
                errorCode |= StackVerifierError::CANARY_LEAK;
                logger::emergencyLog(strFParser::parseF("Data canary protection---end[%p] has leaked: (%" PRIx64 ") != (%" PRIx64 ")!",
                    VER_DATA_CANARY_END_PTR, *VER_DATA_CANARY_END_PTR, stack_POISON_CANARY));
            }
#endif // STACK_CANARY
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
