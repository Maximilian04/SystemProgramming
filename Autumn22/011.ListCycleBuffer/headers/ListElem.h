/**
 * @file Elem.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Element of the list
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LISTELEM_H
#define LISTELEM_H

#include <stdint.h>

class ListElem {
public:
    size_t prev;
    size_t next;
};

#endif // LISTELEM_H
