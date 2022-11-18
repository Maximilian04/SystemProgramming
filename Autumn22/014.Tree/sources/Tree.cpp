#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "loggerTree.h"

#include "Tree.h"

#define VERIFY(obj) if (verify(obj)) { TREE__dump(*obj)); return Error::VERIFIER_ERR; }

/**
 * @brief Tree constructor
 *
 * @param [out] tree Tree
 * @param [in] elemSize Size of an element
 * @param [in] outFunc Pointer to a function for printing elements'es value
 * @return Tree::Error Error code
 */
Tree::Error Tree::ctor(Tree* const tree, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize, ValueOutFunction_t outFunc) {
    assert(tree);

    tree->debugInfo.objName = objName;
    tree->debugInfo.ctorCallLine = ctorCallLine;
    tree->debugInfo.ctorCallFile = ctorCallFile;
    tree->debugInfo.ctorCallFunc = ctorCallFunc;

    tree->root = nullptr;

    tree->elemSize = elemSize;
    tree->outFunc = outFunc;

    // VERIFY(tree);
    return Error::OK;
}

/**
 * @brief Tree destructor
 *
 * @param [out] tree Tree
 * @return Tree::Error Error code
 */
Tree::Error Tree::dtor(Tree* const tree) {
    assert(tree);

    while (!Tree::isEmpty(tree)) {
        // popBack(tree);
    }

    tree->debugInfo.objName = "zzzombie";

    return Error::OK;
}

/**
 * @brief Destroy subtree
 * 
 * @param [out] tree Tree
 * @param [in] iterator Iterator to subtree's root
 * @return Tree::Error Error code   
 */
Tree::Error Tree::destroySubtree(Tree* const tree, TreeIterator* const iterator) {

}

#define MAKE_NEW_ELEMENT                                             \
    TreeElem* const newElem = (TreeElem*)calloc(sizeof(TreeElem), 1); \
    if (!newElem) return Error::MEM_ERR;

#define SET_NEW_ELEMENT_VALUE                       \
    newElem->valuePtr = calloc(tree->elemSize, 1);   \
    if (!newElem->valuePtr) return Error::MEM_ERR;    \
    if (src)                                           \
        memcpy(newElem->valuePtr, src, tree->elemSize); \
    else                                                 \
        memset(newElem->valuePtr, 0, tree->elemSize);

// /**
//  * @brief Push new element to the back of the tree
//  *
//  * @param [out] tree Tree
//  * @param [in] src Pointer to the new element value
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::pushBack(Tree* const tree, void const* const src) { //TODO переписать, там в дальнейших ошибочки могут быть
//     assert(tree);

//     MAKE_NEW_ELEMENT;

//     if (tree->head) {
//         assert(tree->tail);
//         assert(tree->head->next == nullptr);

//         tree->head->next = newElem;
//         newElem->prev = tree->head;
//     } else {
//         assert(!tree->tail);
//         tree->tail = newElem;
//     }
//     tree->head = newElem;

//     SET_NEW_ELEMENT_VALUE;

//     return Error::OK;
// }

// /**
//  * @brief Push new element to the front of the tree
//  *
//  * @param [out] tree Tree
//  * @param [in] src Pointer to the new element value
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::pushFront(Tree* const tree, void const* const src) {
//     assert(tree);

//     MAKE_NEW_ELEMENT;

//     if (tree->tail) {
//         assert(tree->head);
//         assert(tree->tail->prev == nullptr);

//         tree->tail->prev = newElem;
//         newElem->next = tree->tail;
//     } else {
//         assert(!tree->head);
//         tree->head = newElem;
//     }
//     tree->tail = newElem;

//     SET_NEW_ELEMENT_VALUE;

//     return Error::OK;
// }

// /**
//  * @brief Pop an element from the back of the tree
//  *
//  * @param [out] tree Tree
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::popBack(Tree* const tree) {
//     assert(tree);

//     if (!tree->head) {
//         assert(!tree->tail);
//         return Error::EMPTY;
//     }
//     assert(tree->tail);

//     assert(!tree->head->next);
//     TreeElem* elem = tree->head;

//     free(elem->valuePtr);
//     elem->valuePtr = nullptr;

//     if (elem->prev) {
//         tree->head = elem->prev;
//         tree->head->next = nullptr;
//     } else {
//         assert(tree->head == tree->tail);
//         tree->head = nullptr;
//         tree->tail = nullptr;
//     }
//     free(elem);

//     return Error::OK;
// }

// /**
//  * @brief Pop an element from the front of the tree
//  *
//  * @param [out] tree Tree
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::popFront(Tree* const tree) {
//     assert(tree);

//     if (!tree->head) {
//         assert(!tree->tail);
//         return Error::EMPTY;
//     }
//     assert(tree->tail);

//     assert(!tree->tail->prev);
//     TreeElem* elem = tree->tail;

//     free(elem->valuePtr);
//     elem->valuePtr = nullptr;

//     if (elem->next) {
//         tree->tail = elem->next;
//         tree->tail->prev = nullptr;
//     } else {
//         assert(tree->head == tree->tail);
//         tree->head = nullptr;
//         tree->tail = nullptr;
//     }
//     free(elem);

//     return Error::OK;
// }

// /**
//  * @brief Add new element after the element of tree
//  *
//  * @param [out] tree Tree
//  * @param [in] iterator Iterator to the element
//  * @param [in] src Pointer to the new element value
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::emplaceAfter(Tree* const tree, TreeIterator const* const iterator, void const* const src) {
//     assert(tree);
//     assert(iterator);

//     Error err = OK;
//     if (iterator->ptr->next == nullptr) {
//         err = pushBack(tree, src);
//         return err;
//     }

//     MAKE_NEW_ELEMENT;

//     assert(iterator->ptr->next->prev == iterator->ptr);

//     newElem->prev = iterator->ptr;
//     newElem->next = iterator->ptr->next;

//     iterator->ptr->next->prev = newElem;
//     iterator->ptr->next = newElem;

//     SET_NEW_ELEMENT_VALUE;

//     return Error::OK;
// }

// /**
//  * @brief Add new element before the element of tree
//  *
//  * @param [out] tree Tree
//  * @param [in] iterator Iterator to the element
//  * @param [in] src Pointer to the new element value
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::emplaceBefore(Tree* const tree, TreeIterator const* const iterator, void const* const src) {
//     assert(tree);
//     assert(iterator);

//     Error err = OK;
//     if (iterator->ptr->prev == nullptr) {
//         err = pushFront(tree, src);
//         return err;
//     }

//     MAKE_NEW_ELEMENT;


//     assert(iterator->ptr->prev->next == iterator->ptr);

//     newElem->next = iterator->ptr;
//     newElem->prev = iterator->ptr->prev;

//     iterator->ptr->prev->next = newElem;
//     iterator->ptr->prev = newElem;

//     SET_NEW_ELEMENT_VALUE;

//     return Error::OK;
// }

// /**
//  * @brief Add new element to the tree
//  *
//  * @param [out] tree Tree
//  * @param [in] iterator Iterator to the element
//  * @param [in] direction Does need emplace BEFORE or AFTER the element
//  * @param [in] src Pointer to the new element value
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::emplace(Tree* const tree, TreeIterator const* const iterator, Direction direction, void const* const src) {
//     switch (direction) {
//     case Direction::FORWARD:
//         return emplaceAfter(tree, iterator, src);
//     case Direction::BACKWARD:
//         return emplaceBefore(tree, iterator, src);
//     default:
//         assert(0);
//     }

//     return Error::OK;
// }


// /**
//  * @brief Erase element from the tree
//  *
//  * @param [out] tree Tree
//  * @param [out] iterator Iterator to the element
//  * @param [in] direction If iterator will be set to the next or previous element (**nullptr** if there is no such an element)
//  * @return Tree::Error Error code
//  */
// Tree::Error Tree::erase(Tree* const tree, TreeIterator* const iterator, Direction direction) {
//     assert(tree);
//     assert(iterator);

//     Error err = OK;
//     if (iterator->ptr->next == nullptr) {
//         err = popBack(tree);

//         switch (direction) {
//         case Direction::FORWARD:
//             iterator->ptr = nullptr;
//             break;
//         case Direction::BACKWARD:
//             Tree::rbegin(tree, iterator);
//             break;
//         default:
//             assert(0);
//         }

//         return err;
//     }
//     if (iterator->ptr->prev == nullptr) {
//         err = popFront(tree);
//         iterator->ptr = nullptr;

//         switch (direction) {
//         case Direction::FORWARD:
//             Tree::begin(tree, iterator);
//             break;
//         case Direction::BACKWARD:
//             iterator->ptr = nullptr;
//             break;
//         default:
//             assert(0);
//         }

//         return err;
//     }


//     assert(iterator->ptr->prev->next == iterator->ptr);
//     assert(iterator->ptr->next->prev == iterator->ptr);
//     iterator->ptr->prev->next = iterator->ptr->next;
//     iterator->ptr->next->prev = iterator->ptr->prev;

//     TreeElem* elemToSet;
//     switch (direction) {
//     case Direction::FORWARD:
//         elemToSet = iterator->ptr->next;
//         break;
//     case Direction::BACKWARD:
//         elemToSet = iterator->ptr->prev;
//         break;
//     default:
//         assert(0);
//     }

//     free(iterator->ptr->valuePtr);
//     iterator->ptr->valuePtr = nullptr;
//     free(iterator->ptr);

//     iterator->ptr = elemToSet;

//     return Error::OK;
// }

// #undef MAKE_NEW_ELEMENT
// #undef SET_NEW_ELEMENT_VALUE

/**
 * @brief Is tree empty
 *
 * @param [in] tree Tree
 */
bool Tree::isEmpty(Tree const* const tree) {
    assert(tree);
    return !tree->root;
}

// /**
//  * @brief Get the first element of the tree
//  *
//  * @param [in] tree Tree
//  * @param [out] iterator Iterator to the first element
//  * @return Error Error code
//  */
// Tree::Error Tree::begin(Tree const* const tree, TreeIterator* const iterator) {
//     assert(tree);
//     assert(iterator);

//     iterator->ptr = tree->tail;

//     return Error::OK;
// }

// /**
//  * @brief Get the last element of the tree
//  *
//  * @param [in] tree Tree
//  * @param [out] iterator Iterator to the last element
//  * @return Error Error code
//  */
// Tree::Error Tree::rbegin(Tree const* const tree, TreeIterator* const iterator) {
//     assert(tree);
//     assert(iterator);

//     iterator->ptr = tree->head;

//     return Error::OK;
// }

/**
 * @brief Get tree's outFunc
 *
 * @param [in] tree Tree
 * @return ValueOutFunction_t outFunc
 */
ValueOutFunction_t Tree::getOutFunc(Tree const* const tree) {
    assert(tree);

    return tree->outFunc;
}

/**
 * @brief Dump Tree info
 *
 * @param [in] tree Tree
 * @return Tree::Error Error code
 */
Tree::Error Tree::dump(Tree* const tree, LOGFUNCHEAD_ARGS_H) {
    assert(funcName);
    assert(fileName);

    Error err = Error::OK;

    logger::openLogFile();

    logger::logHtmlHead();
    logger__logFuncHead());
    if (tree == nullptr) {
        logger::emergencyLog("Tree is nullptr");
        err = Error::NULLPTR_ERR;
    } else {

        logger::logStructHeadDebug("Tree", tree, &tree->debugInfo);

        logTree(tree);
    }
    logger::logHtmlTail();

    logger::closeLogFile();

    return err;
}
