#include <stdio.h>

#include "tests.h"
#include <List.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    List list;
    List__ctor(list, int, "%d");
    List__dump(list);
    int i = 239;
    List::pushBack(&list);
    List::pushBack(&list, &i);
    i = -127;
    List::pushFront(&list, &i);
    i = -239;
    List::pushFront(&list, &i);
    List__dump(list);
    List::popBack(&list);
    List__dump(list);
    List::popFront(&list);
    List__dump(list);

    ListIterator elem{};
    List::begin(&list, &elem);
    if (*(int*)ListIterator::getValue(&elem) != -127) {
        printf("ATATA!!! 1: %d\n", *(int*)ListIterator::getValue(&elem));
    }
    ListIterator::next(&elem);
    if (*(int*)ListIterator::getValue(&elem) != 0) {
        printf("ATATA!!! 2: %d\n", *(int*)ListIterator::getValue(&elem));
    }

    return 0;
}
