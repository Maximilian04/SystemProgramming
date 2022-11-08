#include <stdio.h>

#include "tests.h"
#include <List.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    List list;
    List__dump(list);

    return 0;
}
