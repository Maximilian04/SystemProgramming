/**
 * @file Stack.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Stack implementation
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdint.h>

#include "..\logger\logger.h"
#include "..\DebugInfo\DebugInfo.h"

typedef int Elem_t;

/*
#define STACK_DEBUG
#ifndef STACK_DEBUG
#else // !STACK_DEBUG
#endif // STACK_DEBUG
*/

#ifdef STACK_DEBUG
class Stack : public Debuggable {
#else // !STACK_DEBUG
class Stack {
#endif // STACK_DEBUG
public:
    Elem_t* data;
    size_t size;
    size_t capacity;
};

typedef uint8_t VerifierCode;
enum StackVerifierError {
    OK            = 0b00000000, ///< No errors
    SIZE_OVER_CAP = 0b00000001, ///< Size is greater than capacity
    BAD_DATA_PTR  = 0b00000010, ///< Wrong data pointer
    POISONE_LEAK  = 0b00000100, ///< Poison in data space or poison leak
};

#define stack_POISON(type)     stack::POISON##type
#define stack_POISON_PTR(type) stack::POISON##type##PTR
#define stack_POISONDEF(type)     const type POISON##type        =         0xCAFED00D
#define stack_POISONDEF_PTR(type) type * const POISON##type##PTR = (type *)0xCAFED00D

namespace stack {
    stack_POISONDEF(Elem_t);
    stack_POISONDEF(size_t);
    stack_POISONDEF_PTR(Elem_t);

    enum Error {
        OK = 0,
        EMPTY,
        DATA_TRUNC,
    };

#ifdef STACK_DEBUG
#define STACK__ctor(obj) stack::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj)
    Error ctor(Stack* const stack, DEBUGINFO_CTOR_ARGS_H, size_t capacity = 0);
#else // !STACK_DEBUG
#define STACK__ctor(obj) stack::ctor(&obj
    Error ctor(Stack* const stack, size_t capacity = 0);
#endif // STACK_DEBUG

    Error dtor(Stack* const stack);

    Error resize(Stack* const stack, size_t newCapacity);

    size_t getSize(Stack* const stack);

    Error push(Stack* const stack, Elem_t elem);
    Error pop(Stack* const stack, Elem_t* const dst = nullptr);
    Error getLast(Stack* const stack, Elem_t* const dst);

#define STACK__dump(stackObj) stack::dump(&stackObj, LOGFUNCHEAD_ARGS_R
    Error dump(Stack* const stack, LOGFUNCHEAD_ARGS_H);

    VerifierCode verify(Stack* const stack);
}

#endif // STACK_H
