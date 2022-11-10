#include <assert.h>

#include "ListIterator.h"

ListIterator::Error ListIterator::next(ListIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    if (!iterator->ptr->next) return Error::LAST_ELEM;
    iterator->ptr = iterator->ptr->next;

    return Error::OK;
}

ListIterator::Error ListIterator::prev(ListIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    if (!iterator->ptr->prev) return Error::FIRST_ELEM;
    iterator->ptr = iterator->ptr->prev;

    return Error::OK;
}

void* ListIterator::getValue(ListIterator const* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr->valuePtr;

    return nullptr;
}


ListElem const* ListIterator::getElemPtr(ListIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr;
}

ListElem const* ListIterator::getNextPtr(ListIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr->next;
}

ListElem const* ListIterator::getPrevPtr(ListIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr->prev;
}
