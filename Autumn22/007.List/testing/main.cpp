#include <stdio.h>

#include "tests.h"
#include <List.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    List list;
    List__ctor(list, sizeof(int));
    int i = 0;
    List::pushBack(&list, &i);
    List::pushBack(&list);
    List__dump(list);

    return 0;
}
