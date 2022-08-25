#include <stdio.h>

#include "testUI.h"
#include "tests.h"

#define FUNC_TO_TEST(FUNC) &test::FUNC, #FUNC

int main(int argc, const char* const* const argv) {
    FILE* testFile = nullptr;

    ProccessFlagsPtrs proccessFlagsPtrs = {
        &testFile
    };

    switch (cmdParser::handleFlags(argc, argv, &reactToFlags, &proccessFlagsPtrs)) {
    case cmdParser::ParserResult::BAD_INPUT:
        return 0;
        break;
    case cmdParser::ParserResult::GOOD_INPUT:
        break;
    default:
        assert(false && "cmdParser::processFlags()'s return is not a cmdParser::PARSER_RESULT's member");
        break;
    }

    char command[MAX_FUNC_NAME_LENGTH] = {};
    bool testInputIsCorrect = true;

    while (fscanf(testFile, "%s", command) != EOF) {

        if (!autoTest::runTest(FUNC_TO_TEST(quadrEquation_solve), command, testFile)) {
            testInputIsCorrect = false;
            printf("TEST INPUT IS INCORRECT");
            break;
        }
    }

    if (autoTest::closeTestFile(testFile) != 0) {
        printf("CANNOT CLOSE TEST FILE CORRECTLY\n");
    }

    if (testInputIsCorrect) {
        printf("TESTS ARE DONE\n");
    }

    return 0;
}
