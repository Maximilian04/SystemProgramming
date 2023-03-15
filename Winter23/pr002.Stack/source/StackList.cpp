#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "StackList.h"

Stack* Stack::stack_ctr(size_t element_size) {
    Stack* ptr = (Stack*)calloc(1, sizeof(Stack));
    if (!ptr) return nullptr;

    ptr->elemSize = element_size;
    ptr->head.data = nullptr;
    ptr->head.prev = nullptr;

    return ptr;
}

int Stack::push(Stack* st, void* buffer) {
    if (!st) return 0;
    if (!buffer) return 0;

    StackElem* newElem = (StackElem*)calloc(1, sizeof(StackElem));
    if (!newElem) return 0;
    newElem->data = calloc(1, st->elemSize);
    if (!newElem->data) return 0;

    memcpy((uint8_t*)newElem->data, buffer, st->elemSize);
    newElem->prev = st->head.prev;
    st->head.prev = newElem;
    return 1; // OK
}

int Stack::top(Stack* st, void* buffer) {
    if (!st) return 0;
    if (!st->head.prev) return 0;
    if (!buffer) return 0;

    if (!st->head.prev->data) return 0;
    memcpy(buffer, (uint8_t*)st->head.prev->data, st->elemSize);
    return 1;
}

int Stack::pop(Stack* st) {
    if (!st) return 0;
    if (!st->head.prev) return 0;

    if (!st->head.prev) return 0;
    StackElem* elemPtr = st->head.prev;
    st->head.prev = elemPtr->prev;

    free(elemPtr->data);
    free(elemPtr);

    return 1;
}

Stack* Stack::stack_dtr(Stack* st) {
    stack_elem_dtr(st->head.prev);

    free(st);

    return nullptr;
}

void Stack::stack_elem_dtr(StackElem* ptr) {
    if (!ptr) return;
    stack_elem_dtr(ptr->prev);
    free(ptr->data);
    free(ptr);
}
