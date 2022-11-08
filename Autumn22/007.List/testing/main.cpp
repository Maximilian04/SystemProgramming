#include <stdio.h>

#include "tests.h"
#include <List.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    List list;
    List__ctor(list, sizeof(int));
    int i = 239;
    List::pushBack(&list);
    List::pushBack(&list, &i);
    List__dump(list);

    ListIterator elem{};
    List::begin(&list, &elem);
    printf("1: %d\n", *(int*)ListIterator::getValue(&elem));
    ListIterator::next(&elem);
    printf("2: %d\n", *(int*)ListIterator::getValue(&elem));

    return 0;
}
