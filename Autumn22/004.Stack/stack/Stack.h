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

namespace stack {
#ifdef STACK_DEBUG
#define STACK__ctor(obj) stack::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj)
    void ctor(Stack* stack, DEBUGINFO_CTOR_ARGS_H, size_t capacity);
#else // !STACK_DEBUG
#define STACK__ctor(obj) stack::ctor(&obj
    void ctor(Stack* stack, size_t capacity);
#endif // STACK_DEBUG
    void dtor(Stack* stack);

    void push(Stack* stack, Elem_t elem);

#define STACK__dump(stackObj) stack::dump(&stackObj, LOGFUNCHEAD_ARGS_R
    void dump(Stack* stack, LOGFUNCHEAD_ARGS_H);
}

#endif // STACK_H
