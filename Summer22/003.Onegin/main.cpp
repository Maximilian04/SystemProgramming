#include <assert.h>
#include <stdio.h>

#include "pervert.h"
#include "cmdParser/cmdParser.h"

int main(int argc, const char* const* const argv) {
    switch (cmdParser::handleFlags(argc, argv, &pervert::reactToFlags, nullptr)) {
    case cmdParser::ParserResult::BAD_INPUT:
        return 0;
        break;
    case cmdParser::ParserResult::GOOD_INPUT:
        break;
    default:
        assert(false && "cmdParser::processFlags()'s return is not a cmdParser::PARSER_RESULT's member");
        break;
    }

    if (pervert::uploadAlphabet()) {
        return 0;
    }

    if (pervert::uploadPoem()) {
        return 0;
    }
    pervert::openOutFile();

    pervert::sortLinesBeginning();
    pervert::writeOutPoem();
    pervert::sortLinesReal();
    pervert::writeOutPoem();
    pervert::sortLinesEnding();
    pervert::writeOutPoem();

    pervert::closeOutFile();
    pervert::destroyAll();

    return 0;
}
