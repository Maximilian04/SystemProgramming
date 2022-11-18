/**
 * @file Elem.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Element of the tree
 * @date 2022-11-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TREEELEM_H
#define TREEELEM_H

class TreeElem {
public:
    void* valuePtr;
    TreeElem* left;
    TreeElem* right;
};

#endif // TREEELEM_H
