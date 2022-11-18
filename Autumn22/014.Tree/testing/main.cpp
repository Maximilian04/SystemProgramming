#include <stdio.h>

#include "tests.h"
#include <Tree.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    Tree tree{};
    Tree__ctor(tree, int, "%d");
    // Tree__dump(tree);
    int i = 1;
    Tree::addRoot(&tree, &i);
    
    TreeIterator node{};
    Tree::set2Root(&tree, &node);

    Tree::addLeft(&tree, &node);
    Tree::addRight(&tree, &node, &i);
    // i = -1;
    // Tree::pushFront(&tree, &i);
    // i = -2;
    // Tree::pushFront(&tree, &i);
    // i = -3;
    // Tree::pushFront(&tree, &i);
    // i = -4;
    // Tree::pushFront(&tree, &i);
    // i = -5;
    // Tree::pushFront(&tree, &i);
    // i = -6;
    // Tree::pushFront(&tree, &i);
    // Tree__dump(tree);
    // Tree::popBack(&tree);
    // Tree__dump(tree);
    // Tree::popFront(&tree);
    // Tree__dump(tree);

    // TreeIterator elem{};
    // Tree::begin(&tree, &elem);
    // Tree::erase(&tree, &elem);
    // Tree__dump(tree);
    // Tree::begin(&tree, &elem);
    // TreeIterator::next(&elem);
    // TreeIterator::next(&elem);
    // TreeIterator::next(&elem);
    // TreeIterator::next(&elem);
    // TreeIterator::prev(&elem);
    // Tree::erase(&tree, &elem);
    // Tree__dump(tree);

    // Tree::dtor(&tree);
    // Tree__dump(tree);

    return 0;
}
