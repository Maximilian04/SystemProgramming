#include <assert.h>

#include "ListIterator.h"

ListIterator::Error ListIterator::next(List const* const list, ListIterator* const iterator) {
    assert(list);
    assert(iterator);
    assert(iterator->ptr);

    if (!(list->bufferElem[iterator->ptr].next)) return Error::LAST_ELEM;
    iterator->ptr = list->bufferElem[iterator->ptr].next;

    return Error::OK;
}

ListIterator::Error ListIterator::prev(List const* const list, ListIterator* const iterator) {
    assert(list);
    assert(iterator);
    assert(iterator->ptr);

    if (!(list->bufferElem[iterator->ptr].prev)) return Error::FIRST_ELEM;
    iterator->ptr = list->bufferElem[iterator->ptr].prev;

    return Error::OK;
}

void* ListIterator::getValue(List const* const list, ListIterator const* const iterator) {
    assert(list);
    assert(iterator);
    assert(iterator->ptr);

    return (uint8_t*)list->bufferValue + list->elemSize * iterator->ptr;
}


size_t ListIterator::getElemPtr(List const* const list, ListIterator const* const iterator) {
    assert(list);
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr;
}

size_t ListIterator::getNextPtr(List const* const list, ListIterator const* const iterator) {
    assert(list);
    assert(iterator);
    assert(iterator->ptr);

    return list->bufferElem[iterator->ptr].next;
}

size_t ListIterator::getPrevPtr(List const* const list, ListIterator const* const iterator) {
    assert(list);
    assert(iterator);
    assert(iterator->ptr);

    return list->bufferElem[iterator->ptr].prev;
}
