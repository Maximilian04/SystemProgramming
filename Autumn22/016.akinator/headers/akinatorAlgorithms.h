/**
 * @file akinatorAlgorithms.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Algorithms for akinator
 * @date 2022-12-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef AKINATORALGORITHMS_H
#define AKINATORALGORITHMS_H

#include "Akinator.h"

namespace akinatorAlgorithms {
    struct FinderResult {
        TreeIterator bestNode;
        size_t depth;
    };
    Akinator::Error findNode(Akinator* const akinator, char const* keyword, FinderResult* result);

    struct FeatsList { 
        char const* feat;
        bool correct;
    };
    Akinator::Error getNodeOrigin(Akinator* const akinator, TreeIterator node, size_t maxDepth, FeatsList* result);
}

#endif // AKINATORALGORITHMS_H
