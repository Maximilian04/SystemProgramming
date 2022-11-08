#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "List.h"

#define VERIFY(obj) if (verify(obj)) { LIST__dump(*obj)); return Error::VERIFIER_ERR; }

List::Error List::pushBack(List* list, size_t size, void* src) {
    assert(list != nullptr);
    // assert(src != nullptr);

    ListElem* newElem = (ListElem*)calloc(sizeof(ListElem), 1);
    if (!newElem) return Error::MEM_ERR;

    if (list->head) {
        assert(list->head->next == nullptr);

        list->head->next = newElem;
        newElem->prev = list->head;
        list->head = newElem;
    }

    list->head->valuePtr = calloc(size, 1);
    if (!list->head->valuePtr) return Error::MEM_ERR;
    memcpy(list->head->valuePtr, src, size);

    return Error::OK;
}
