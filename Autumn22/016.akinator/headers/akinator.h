/**
 * @file Akinator.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief
 * @date 2022-11-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef AKINATOR_H
#define AKINATOR_H

#include <Tree.h>

class Akinator {
public:
    Tree data;

    DebugInfo debugInfo;

    enum Error {
        OK = 0,      ///< No errors
        MEM_ERR,     ///< Error in memory allocation
        NULLPTR_ERR, ///< Nullptr is occured
        EMPTY,       ///< No elements in tree
    };

    static Error ctor(Akinator* const akinator, DEBUGINFO_CTOR_ARGS_H);
};

#endif // AKINATOR_H
