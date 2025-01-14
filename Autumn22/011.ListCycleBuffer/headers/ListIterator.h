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
    size_t ptr;

    enum Error {
        OK = 0,     ///< No errors
        FIRST_ELEM, ///< The first element is reached
        LAST_ELEM,  ///< The last element is reached
    };

    static Error next(List const* const list, ListIterator* const iterator);
    static Error prev(List const* const list, ListIterator* const iterator);
    static void* getValue(List const* const list, ListIterator const* const iterator);

    static size_t getElemPtr(List const* const list, ListIterator const* const iterator);
    static size_t getNextPtr(List const* const list, ListIterator const* const iterator);
    static size_t getPrevPtr(List const* const list, ListIterator const* const iterator);
};

#endif // LISTITERATOR_H
