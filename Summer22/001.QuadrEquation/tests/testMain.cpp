#include <stdio.h>

#include "testUI.h"
#include "autoTest.h"
#include "tests.h"

#define FUNC_TO_TEST(FUNC) &test::FUNC, #FUNC

int main(int argc, const char* const* const argv) {
    int programMode = ProgramMode::STD_TEST_FILE;
    const char* userTestFileName;

    ProccessFlagsPtrs proccessFlagsPtrs = {
        &programMode,
        &userTestFileName
    };

    switch (cmdParser::processFlags(argc, argv, &proccessFlagsPtrs)) {
    case cmdParser::ParserResult::BAD_INPUT:
        return 0;
        break;
    case cmdParser::ParserResult::GOOD_INPUT:
        break;
    default:
        assert(false && "cmdParser::processFlags()'s return is not a cmdParser::PARSER_RESULT's member");
        break;
    }

    FILE* testFile = autoTest::openTestFile((programMode & EXT_TEST_FILE), userTestFileName);

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
