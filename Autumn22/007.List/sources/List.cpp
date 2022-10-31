#include <assert.h>
#include <stdio.h>

#include "List.h"

List::Error List::pushBack(List* list, size_t size, void* src) {
    assert(list != nullptr);
    // assert(src != nullptr);

    ListElem* newElem = (ListElem*)calloc(size, 1);
    if (!newElem) return Error::MEM_ERR;

    if (list->head) {
        assert(list->head->next == nullptr);

        list->head->next = newElem;
        newElem->prev = list->head;
        list->head = newElem;
    }

    return Error::OK;
}
