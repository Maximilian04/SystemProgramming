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

    if (cmdParser::handleFlags(argc, argv, cmdParser::reactToFlags, &proccessFlagsPtrs))
        return 1;


    Akinator akinator{};
    Akinator__ctor(akinator);

    if (Akinator::upload(&akinator, databaseFileName)) {
        printf("upload error\n");
        return 1;
    }
    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_NOTE_TEXTCOLOR, "begin:"));
    Tree__dump(akinator.data);


    switch (mode) {
    case Mode::GUESS:
        if (Akinator::guess(&akinator))
            return 1;
        break;
    case Mode::DEFENITION:
        if (Akinator::defenition(&akinator))
            return 1;
        break;
    case Mode::DIFFERENCE:
        if (Akinator::difference(&akinator))
            return 1;
        break;
    default:
        assert(0);
    }


    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_NOTE_TEXTCOLOR, "end:"));
    Tree__dump(akinator.data);
    if (Akinator::save(&akinator, databaseFileName)) {
        printf("File error\n");
        return 1;
    }

    Akinator::dtor(&akinator);

    printf("Program finished 0\n");

    return 0;
}
