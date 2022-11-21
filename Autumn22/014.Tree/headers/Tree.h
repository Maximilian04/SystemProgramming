/**
 * @file Tree.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Tree of object
 * @date 2022-11-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TREE_H
#define TREE_H

#include <ValueOutFunction_t.h>
#include <logger.h>

#include "TreeElem.h"
#include "TreeIterator.h"

class Tree {
public:
    TreeElem* root;

    size_t elemSize;
    ValueOutFunction_t outFunc;

    DebugInfo debugInfo;

    enum Error {
        OK = 0,      ///< No errors
        MEM_ERR,     ///< Error in memory allocation
        NULLPTR_ERR, ///< Nullptr is occured
        EMPTY,       ///< No elements in tree
    };

#define Tree__ctor(obj, type, printfTemplate) Tree::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj), sizeof(type), \
    [](ValueOutFunction_t_PARAMS) -> char const* {                                                         \
        return strFParser::parseFNBuf(bufN, printfTemplate, *(type const*)valuePtr);                        \
    })
    static Error ctor(Tree* const tree, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize, ValueOutFunction_t outFunc);
    static Error dtor(Tree* const tree);

    static Error destroySubtree(Tree* const tree, TreeIterator* const iterator);

    // static Error pushBack (Tree* const tree, void const* const src = nullptr);
    // static Error pushFront(Tree* const tree, void const* const src = nullptr);
    // static Error popBack  (Tree* const tree);
    // static Error popFront (Tree* const tree);

    // enum Direction {
    //     FORWARD = 1,
    //     BACKWARD = 0,
    // };
    // static Error insertAfter (Tree* const tree, TreeIterator const* const iterator,                      void const* const src = nullptr);
    // static Error insertBefore(Tree* const tree, TreeIterator const* const iterator,                      void const* const src = nullptr);
    // static Error insert      (Tree* const tree, TreeIterator const* const iterator, Direction direction, void const* const src = nullptr);
    // static Error erase        (Tree* const tree, TreeIterator      * const iterator, Direction direction = Direction::FORWARD);

    static bool isEmpty(Tree const* const tree);

    static Error set2Root(Tree const* const tree, TreeIterator* const iterator);

    static Error addRoot( Tree* const tree,                               void const* const src = nullptr);
    static Error addLeft( Tree* const tree, TreeIterator* const iterator, void const* const src = nullptr);
    static Error addRight(Tree* const tree, TreeIterator* const iterator, void const* const src = nullptr);

    static ValueOutFunction_t getOutFunc(Tree const* const tree);

#define DfsCallbackFunction_t_PARAMS Tree const* const tree, TreeIterator const* const iterator, void* userdata
typedef void (*DfsCallbackFunction_t)(DfsCallbackFunction_t_PARAMS);

#define DFSCALLBACKLIST_PARAMS              \
    DfsCallbackFunction_t  preorderCallback, \
    DfsCallbackFunction_t   inorderCallback,  \
    DfsCallbackFunction_t postorderCallback
#define DFSCALLBACKLIST preorderCallback, inorderCallback, postorderCallback
    static Error dfs(Tree* const tree, DFSCALLBACKLIST_PARAMS, void* userdata = nullptr, TreeIterator const* const rootNode = nullptr);

#define Tree__dump(stackObj) Tree::dump(&stackObj, LOGFUNCHEAD_ARGS_R)
    static Error dump(Tree* const tree, LOGFUNCHEAD_ARGS_H);
};

#endif // TREE_H
