#include <assert.h>

#include "TreeIterator.h"

TreeIterator::Error TreeIterator::left(TreeIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    if (!iterator->ptr->left) return Error::LAST_ELEM;
    iterator->ptr = iterator->ptr->left;

    return Error::OK;
}

TreeIterator::Error TreeIterator::right(TreeIterator* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    if (!iterator->ptr->right) return Error::FIRST_ELEM;
    iterator->ptr = iterator->ptr->right;

    return Error::OK;
}

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
