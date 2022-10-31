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

#include "ListElem.h"

class List {
public:
    ListElem* head;
    ListElem* tail;

    enum Error {
        OK = 0,  ///< No errors
        MEM_ERR, ///< Error in memory allocation
    };

    static Error pushBack(List* list, size_t size, void* src = nullptr);
};

#endif // LIST_H
