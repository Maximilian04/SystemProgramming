/**
 * @file List.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief List of object
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIST_H
#define LIST_H

#include <logger.h>

#include "ListElem.h"
#include "ListIterator.h"

class List {
public:
    ListElem* head;
    ListElem* tail;

    size_t elemSize;

    DebugInfo debugInfo;

    enum Error {
        OK = 0,      ///< No errors
        MEM_ERR,     ///< Error in memory allocation
        NULLPTR_ERR, ///< Nullptr is occured
    };

#define List__ctor(obj, ...) List::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj) __VA_OPT__(, __VA_ARGS__))
    static Error ctor(List* const list, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize);
    static Error dtor(List* const list);

    static Error pushBack(List* const list, void const* const src = nullptr);

    static bool isEmpty(List const* const list);

    static Error begin(List const* const list, ListIterator* const iterator);
    static Error rbegin(List const* const list, ListIterator* const iterator);

#define List__dump(stackObj) List::dump(&stackObj, LOGFUNCHEAD_ARGS_R)
    static Error dump(List* const list, LOGFUNCHEAD_ARGS_H);
};

#endif // LIST_H
