#include <assert.h>

#include "cmdParsing.h"
#include "recDescent.h"

int main(int argc, const char* const* const argv) {
    FILE* inputFile = nullptr;

    cmdParser::ProccessFlagsPtrs proccessFlagsPtrs = {
        &inputFile
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


    char buffer[256];
    int fscanfRes = fscanf(inputFile, "%s", buffer);
    if (fscanfRes != 1) {
        printf("Invalid text in file\n");
    } else {
        double res = recDescent::getG(buffer);

        printf("Result : '%f'\n", res);
    }


    cmdParser::closeFile(inputFile);
    printf("Program finished 0\n");

    return 0;
}