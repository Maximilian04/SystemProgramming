#include <assert.h>
#include <stdio.h>

#include "Akinator.h"

int main(int argc, const char* const* const argv) {
    Akinator akinator{};
    Akinator__ctor(akinator);

    Tree::addRoot(&akinator.data, "rootь");
    TreeIterator it{};
    Tree::set2Root(&akinator.data, &it);
    Tree::addRight(&akinator.data, &it, "leftь");

    if (Akinator::save(&akinator, "data.txt")) {
        printf("File error\n");
        return 1;
    }

    printf("Program finished 0\n");

    return 0;
}
