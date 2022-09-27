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

#include "..\logger\loggerIncludeDefines.h"

typedef int Elem_t;

struct Stack {
    Elem_t* data;
    size_t size;
    size_t capacity;
};

namespace stack {
    void ctor(Stack* stack, size_t capacity);
    void dtor(Stack* stack);

    void push(Stack* stack, Elem_t elem);

#define STACK_dump(stack) stack::dump(&stack, LOGFUNCHEAD_PARAMS_R);
    void dump(Stack* stack, LOGFUNCHEAD_PARAMS_H);
}

#endif // STACK_H
