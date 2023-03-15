#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "StackArr.h"

Stack* Stack::stack_ctr(size_t size) {
    return stack_ctr(size, 0);
}

Stack* Stack::stack_ctr(size_t size, size_t element_size) {
    Stack* st = (Stack*)calloc(1, sizeof(Stack));
    if (!st) return nullptr;

    st->elemSize = element_size;
    st->capacity = size;
    st->size = 0;
    st->data = calloc(st->capacity, st->elemSize);
    if (!st->data) return stack_dtr(st);

    return st;
}

int Stack::push(Stack* st, void* buffer) {
    if (!st) return 0;
    if (!st->data) return 0;
    if (!buffer) return 0;

    if (st->capacity == st->size && !stack_realloc(st)) return 0;

    // st->capacity < st->size

    memcpy((uint8_t*)st->data + (st->size++) * st->elemSize, buffer, st->elemSize);
    return 1; // OK
}

int Stack::top(Stack* st, void* buffer) {
    if (!st) return 0;
    if (!st->data) return 0;
    if (!buffer) return 0;

    if (!st->size) return 0;
    memcpy(buffer, (uint8_t*)st->data + (st->size - 1) * st->elemSize, st->elemSize);
    return 1;
}

int Stack::pop(Stack* st) {
    if (!st) return 0;
    if (!st->data) return 0;

    if (!st->size) return 0;
    st->size--;
    return 1;
}

Stack* Stack::stack_dtr(Stack* st) {
    free(st->data);
    free(st);

    return nullptr;
}

int Stack::stack_realloc(Stack* st) {
    void* newData = realloc(st->data, st->size << 1);
    if (!newData) return 0;

    st->data = newData;
    st->size <<= 1;
    return 1;
}
