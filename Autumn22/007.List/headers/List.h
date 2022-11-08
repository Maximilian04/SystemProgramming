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

#ifndef NDEBUG

#ifdef LIST_DEBUG
#else // !LIST_DEBUG
#define LIST_DEBUG
#endif // LIST_DEBUG

#endif // LIST_DEBUG

class List {
public:
    ListElem* head;
    ListElem* tail;

#ifdef LIST_DEBUG
    DebugInfo debugInfo;
#endif // LIST_DEBUG

    enum Error {
        OK = 0,      ///< No errors
        MEM_ERR,     ///< Error in memory allocation
        NULLPTR_ERR, ///< Nullptr is occured
    };

    static Error pushBack(List* const list, size_t const size, void const* const src = nullptr);

#define List__dump(stackObj) List::dump(&stackObj, LOGFUNCHEAD_ARGS_R)
    static Error dump(List* const list, LOGFUNCHEAD_ARGS_H);
};

#endif // LIST_H
