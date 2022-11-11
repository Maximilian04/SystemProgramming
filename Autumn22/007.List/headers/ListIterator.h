/**
 * @file ListIterator.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Iterator to an element of list
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LISTITERATOR_H
#define LISTITERATOR_H

class ListIterator;

#include "List.h"

class ListIterator {
public:
    ListElem* ptr;

    enum Error {
        OK = 0,     ///< No errors
        FIRST_ELEM, ///< The first element is reached
        LAST_ELEM,  ///< The last element is reached
    };

    static Error next(ListIterator* const iterator);
    static Error prev(ListIterator* const iterator);
    static void* getValue(ListIterator const* const iterator);

    static ListElem const* getElemPtr(ListIterator const* const iterator);
    static ListElem const* getNextPtr(ListIterator const* const iterator);
    static ListElem const* getPrevPtr(ListIterator const* const iterator);
};

#endif // LISTITERATOR_H
