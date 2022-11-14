#include <stdio.h>

#include "tests.h"
#include <List.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    List list;
    List__ctor(list, int, "%d", 10);
    List__dump(list);
    int i = 1;
    List::pushBack(&list);
    List__dump(list);
    List::pushBack(&list, &i);
    i = -1;
    List::pushFront(&list, &i);
    i = -2;
    List::pushFront(&list, &i);
    i = -3;
    List::pushFront(&list, &i);
    i = -4;
    List::pushFront(&list, &i);
    i = -5;
    List::pushFront(&list, &i);
    i = -6;
    List::pushFront(&list, &i);
    List__dump(list);
    List::pushBack(&list, &i);
    // List::popBack(&list);
    List__dump(list);
    List::resize(&list, 20);
    List__dump(list);
    List::pushBack(&list, &i);
    // List::popFront(&list);
    List__dump(list);

    ListIterator elem{};
    List::begin(&list, &elem);
    // List::erase(&list, &elem);
    List__dump(list);
    List::begin(&list, &elem);
    ListIterator::next(&list, &elem);
    ListIterator::next(&list, &elem);
    ListIterator::next(&list, &elem);
    ListIterator::next(&list, &elem);
    ListIterator::prev(&list, &elem);
    // List::erase(&list, &elem);
    List__dump(list);
    List::linearize(&list);
    List__dump(list);

    List::dtor(&list);
    List__dump(list);

    return 0;
}
