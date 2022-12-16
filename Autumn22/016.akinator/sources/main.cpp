#include <assert.h>
#include <stdio.h>

#include "include.h"
#include "cmdParsing.h"
#include "Akinator.h"

int main(int argc, const char* const* const argv) {
    Mode mode = Mode::GUESS;
    char const* databaseFileName = "data.txt";

    cmdParser::ProccessFlagsPtrs proccessFlagsPtrs = {
        &mode,
        &databaseFileName,
    };

    switch (cmdParser::handleFlags(argc, argv, cmdParser::reactToFlags, &proccessFlagsPtrs)) {
    case cmdParser::ParserResult::BAD_INPUT:
        return 1;
        break;
    case cmdParser::ParserResult::GOOD_INPUT:
        break;
    default:
        assert(false && "cmdParser::processFlags()'s return value is not an allowed cmdParser::PARSER_RESULT's member");
        break;
    }


    Akinator akinator{};
    Akinator__ctor(akinator);

    if (Akinator::upload(&akinator, databaseFileName)) {
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


    if (Akinator::save(&akinator, databaseFileName)) {
        printf("File error\n");
        return 1;
    }
    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_NOTE_TEXTCOLOR, "end:"));
    Tree__dump(akinator.data);

    Tree::dtor(&akinator.data);

    printf("Program finished 0\n");

    return 0;
}
