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

typedef char const* (*ListOutFunction_t)(size_t, void*);

class List {
public:
    ListElem* head;
    ListElem* tail;

    size_t elemSize;
    ListOutFunction_t outFunc;

    DebugInfo debugInfo;

    enum Error {
        OK = 0,      ///< No errors
        MEM_ERR,     ///< Error in memory allocation
        NULLPTR_ERR, ///< Nullptr is occured
        EMPTY,       ///< No elements in list
    };

#define List__ctor(obj, type, printfTemplate) List::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj), sizeof(type), \
    [](size_t bufN, void* valuePtr) -> char const* {                                                       \
        return strFParser::parseFNBuf(bufN, printfTemplate, *(type*)valuePtr);                              \
    })
    static Error ctor(List* const list, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize, ListOutFunction_t outFunc);
    static Error dtor(List* const list);

    static Error pushBack(List* const list, void const* const src = nullptr);
    static Error pushFront(List* const list, void const* const src = nullptr);
    static Error popBack(List* const list);
    static Error popFront(List* const list);

    enum Direction {
        FORWARD = 1,
        BACKWARD = 0,
    };
    static Error emplaceAfter (List* const list, ListIterator const* const iterator,                      void const* const src = nullptr);
    static Error emplaceBefore(List* const list, ListIterator const* const iterator,                      void const* const src = nullptr);
    static Error emplace      (List* const list, ListIterator const* const iterator, Direction direction, void const* const src = nullptr);
    static Error erase        (List* const list, ListIterator      * const iterator, Direction direction = Direction::FORWARD);

    static bool isEmpty(List const* const list);

    static Error begin(List const* const list, ListIterator* const iterator);
    static Error rbegin(List const* const list, ListIterator* const iterator);

#define List__dump(stackObj) List::dump(&stackObj, LOGFUNCHEAD_ARGS_R)
    static Error dump(List* const list, LOGFUNCHEAD_ARGS_H);
};

#endif // LIST_H
