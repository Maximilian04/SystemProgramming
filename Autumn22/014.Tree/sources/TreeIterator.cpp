#include <assert.h>

#include "TreeIterator.h"

TreeIterator::Error TreeIterator::copyTo(TreeIterator* const src, TreeIterator* const dst) {
    assert(src);
    assert(dst);

    dst->ptr = src->ptr;

    return Error::OK;
}


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

bool TreeIterator::isValid(TreeIterator const* const iterator) {
    assert(iterator);

    return iterator->ptr;
}


TreeElem const* TreeIterator::getElemPtr(TreeIterator const* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr;
}

TreeElem const* TreeIterator::getLeftPtr(TreeIterator const* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr->left;
}

TreeElem const* TreeIterator::getRightPtr(TreeIterator const* const iterator) {
    assert(iterator);
    assert(iterator->ptr);

    return iterator->ptr->right;
}
