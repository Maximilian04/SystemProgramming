#include <stdio.h>

#include "testUI.h"
#include "autoTest.h"
#include "tests.h"

#define FUNC_TO_TEST(FUNC) &test::FUNC, #FUNC

int main(int argc, char** argv) {
    int programMode = ProgramMode::STD_TEST_FILE;
    char userTestFileName[MAX_CMD_ARG_LENGTH] = {};
    // TODO убрать две strcpy

    ProccessFlagsPtrs proccessFlagsPtrs = {
        &programMode,
        userTestFileName
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

    FILE* testFile = autoTest::openTestFile((programMode & EXT_TEST_FILE), proccessFlagsPtrs.userTestFileName);

    char command[MAX_FUNC_NAME_LENGTH] = {};

    while (fscanf(testFile, "%s", command) != EOF) {

        if (!autoTest::runTest(FUNC_TO_TEST(quadrEquation_solve), command, testFile)) {
            printf("TEST INPUT IS INCORRECT");
            return 0;
        }
    }

    printf("TESTS ARE DONE\n");
    return 0;
}
