#include <assert.h>
#include <stdio.h>

#include "Akinator.h"

const size_t INPUT_BUFFER_SIZE = 512;

int main(int argc, const char* const* const argv) {
    Akinator akinator{};
    Akinator__ctor(akinator);

    if (Akinator::upload(&akinator, "data.txt")) {
        printf("upload error\n");
        return 1;
    }
    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_NOTE_TEXTCOLOR, "begin:"));
    Tree__dump(akinator.data);


    TreeIterator position{};
    Tree::set2Root(&akinator.data, &position);

    size_t bufN = strFParser::addCallocBuf();
    char input[INPUT_BUFFER_SIZE];
    while (TreeIterator::getRightPtr(&position)) {
        printf("%s\n", Tree::getOutFunc(&akinator.data)(bufN, TreeIterator::getValue(&position)));
        scanf("%s", input);

        if (*input == 'y')
            TreeIterator::right(&position);
        else
            TreeIterator::left(&position);
    }

    printf("Is it %s?\n", Tree::getOutFunc(&akinator.data)(bufN, TreeIterator::getValue(&position)));
    scanf("%s", input);

    if (*input == 'y')
        printf("Yeeee\n");
    else
        printf("Nooo0o\n");


    if (Akinator::save(&akinator, "data.txt")) {
        printf("File error\n");
        return 1;
    }
    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_NOTE_TEXTCOLOR, "end:"));
    Tree__dump(akinator.data);

    Tree::dtor(&akinator.data);

    printf("Program finished 0\n");

    return 0;
}
