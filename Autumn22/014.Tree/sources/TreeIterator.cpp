#include <assert.h>

#include "TreeIterator.h"

// TreeIterator::Error TreeIterator::next(TreeIterator* const iterator) {
//     assert(iterator);
//     assert(iterator->ptr);

//     if (!iterator->ptr->next) return Error::LAST_ELEM;
//     iterator->ptr = iterator->ptr->next;

//     return Error::OK;
// }

// TreeIterator::Error TreeIterator::prev(TreeIterator* const iterator) {
//     assert(iterator);
//     assert(iterator->ptr);

//     if (!iterator->ptr->prev) return Error::FIRST_ELEM;
//     iterator->ptr = iterator->ptr->prev;

//     return Error::OK;
// }

void* TreeIterator::getValue(TreeIterator const* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr->valuePtr;

    return nullptr;
}


// TreeElem const* TreeIterator::getElemPtr(TreeIterator const* const iterator) {
//     assert(iterator);
//     assert(iterator->ptr);

//     return iterator->ptr;
// }

// TreeElem const* TreeIterator::getNextPtr(TreeIterator const* const iterator) {
//     assert(iterator);
//     assert(iterator->ptr);

//     return iterator->ptr->next;
// }

// TreeElem const* TreeIterator::getPrevPtr(TreeIterator const* const iterator) {
//     assert(iterator);
//     assert(iterator->ptr);

//     return iterator->ptr->prev;
// }
