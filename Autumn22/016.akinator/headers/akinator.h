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
        OK = 0,              ///< No errors
        MEM_ERR,             ///< Error in memory allocation
        NULLPTR_ERR,         ///< Nullptr is occured
        EMPTY,               ///< No elements in tree
        FILE_ERR,            ///< Error with file writing or reading
        FILE_FORMAT_ERR,     ///< Error with input file format
        UPLOAD_TO_NOT_EMPTY, ///< Tree to upload is not empty
        FINDER_ERR,          ///< Error in finder function
    };

#define Akinator__ctor(obj) Akinator::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj))
    static Error ctor(Akinator* const akinator, DEBUGINFO_CTOR_ARGS_H);
    static Error dtor(Akinator* const akinator);

    static Error save(Akinator const* const akinator, char const* const fileName);
    static Error upload(Akinator* const akinator, char const* const fileName);

    struct FinderResult {
        TreeIterator bestNode;
        size_t depth;
    };
    static Error findNode(Akinator* const akinator, char const* keyword, FinderResult* result);

    static Error guess(Akinator* const akinator);
    static Error defenition(Akinator* const akinator);
};

#endif // AKINATOR_H
