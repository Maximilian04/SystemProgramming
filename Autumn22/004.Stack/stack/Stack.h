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

#ifndef STACKLIBWORLD
#include "logger\logger.h"
#include "DebugInfo\DebugInfo.h"
#include "hash\hash.h"
#endif // STACKLIBWORLD

typedef uint8_t Elem_t;

#ifndef NDEBUG
#ifdef STACK_DEBUG
#else // !STACK_DEBUG
#define STACK_DEBUG
#endif // STACK_DEBUG

#ifdef STACK_CANARY
#else // !STACK_CANARY
#define STACK_CANARY
#endif // STACK_CANARY

#ifdef STACK_HASH
#else // !STACK_HASH
#define STACK_HASH
#endif // STACK_HASH
#endif // NDEBUG


#ifdef STACK_CANARY
#define stack_POISON_CANARY POISONCanary_t
#endif // STACK_CANARY
#define stack_POISON(type)     stack::POISON##type
#define stack_POISON_PTR(type) stack::POISON##type##PTR
#define stack_POISONDEF(type)     const type POISON##type        =         0xCAFED00D
#define stack_POISONDEF_PTR(type) type * const POISON##type##PTR = (type *)0xCAFED00D

#ifdef STACK_CANARY
typedef uint64_t Canary_t;
#endif // STACK_CANARY

class Stack {
public:
#ifdef STACK_CANARY
    Canary_t canaryBegin;
#endif // STACK_CANARY
    Elem_t* data;
    size_t size;
    size_t capacity;

#ifdef STACK_DEBUG
    DebugInfo debugInfo;
#endif // STACK_DEBUG
#ifdef STACK_HASH
    Hash_t hash;
#endif // STACK_HASH
#ifdef STACK_CANARY
    uint64_t canaryEnd;
#endif // STACK_CANARY
};

typedef uint8_t VerifierCode;
enum StackVerifierError {
    OK            = 0b00000000, ///< No errors
    SIZE_OVER_CAP = 0b00000001, ///< Size is greater than capacity
    BAD_DATA_PTR  = 0b00000010, ///< Wrong data pointer
    POISONE_LEAK  = 0b00000100, ///< Poison in data space or poison leak
    NULLPTR_ERR   = 0b00001000, ///< Got nullptr as object
    HASH_ERR      = 0b00010000, ///< Wrong hash
#ifdef STACK_CANARY
    CANARY_LEAK   = 0b00010000, ///< Defect in canary protection
#endif // STACK_CANARY
};

namespace stack {
    // stack_POISONDEF(Elem_t);
    const Elem_t POISONElem_t = 0xD;
    stack_POISONDEF(size_t);
    stack_POISONDEF(Hash_t);
    stack_POISONDEF_PTR(Elem_t);
#ifdef STACK_CANARY
    const Canary_t stack_POISON_CANARY = 0xFEE1DEADFACEBEAD;
#endif // STACK_CANARY

    enum Error {
        OK = 0,
        EMPTY,
        DATA_TRUNC,
        NULLPTR_ERR,
        VERIFIER_ERR,
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
