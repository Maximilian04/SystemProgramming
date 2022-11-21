/**
 * @file TreeIterator.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Iterator to an element of tree
 * @date 2022-11-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TREEITERATOR_H
#define TREEITERATOR_H

class TreeIterator;

#include "Tree.h"

class TreeIterator {
public:
    TreeElem* ptr;

    enum Error {
        OK = 0,     ///< No errors
        FIRST_ELEM, ///< The first element is reached
        LAST_ELEM,  ///< The last element is reached
    };

    static Error left(TreeIterator* const iterator);
    static Error right(TreeIterator* const iterator);
    static void* getValue(TreeIterator const* const iterator);

    static bool isValid(TreeIterator const* const iterator);

    static TreeElem const* getElemPtr(TreeIterator const* const iterator);
    static TreeElem const* getLeftPtr(TreeIterator const* const iterator);
    static TreeElem const* getRightPtr(TreeIterator const* const iterator);
};

#endif // TREEITERATOR_H
