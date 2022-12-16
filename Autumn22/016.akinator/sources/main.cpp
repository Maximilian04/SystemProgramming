#include <assert.h>
#include <stdio.h>

#include "Akinator.h"

int main(int argc, const char* const* const argv) {
    Akinator akinator{};
    Akinator__ctor(akinator);

    char const* s = "roooaaapppt";
    Tree::addRoot(&akinator.data, &s);
    TreeIterator it{};
    Tree::set2Root(&akinator.data, &it);
    s = "leefaaapppt";
    Tree::addRight(&akinator.data, &it, &s);

    Tree__dump(akinator.data);

    if (Akinator::save(&akinator, "data.txt")) {
        printf("File error\n");
        return 1;
    }

    Akinator akinator2{};
    Akinator__ctor(akinator2);

    if (Akinator::upload(&akinator2, "data.txt")) {
        printf("upload error\n");
        return 1;
    }

    if (Akinator::save(&akinator2, "data2.txt")) {
        printf("File error\n");
        return 1;
    }
    Tree__dump(akinator2.data);

    printf("Program finished 0\n");

    return 0;
}
