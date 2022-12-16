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
        Akinator::guess(&akinator);
        break;
    case Mode::DEFENITION:
        break;
    default:
        assert(0);
    }


    if (Akinator::save(&akinator, databaseFileName)) {
        printf("File error\n");
        return 1;
    }
    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_NOTE_TEXTCOLOR, "end:"));
    Tree__dump(akinator.data);

    Akinator::dtor(&akinator);

    printf("Program finished 0\n");

    return 0;
}
