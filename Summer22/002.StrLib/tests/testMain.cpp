#include <stdio.h>
#include <assert.h>

#include "testingSystem\testUI.h"
#include "tests.h"

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
        bool doesTestExist = false;

        for (const test::TestFuncInfo testFunc : test::testFuncList) {
            switch (autoTest::runTest(testFunc.func, testFunc.name, command, testFile)) {
            case TestResult::PASSED:
            case TestResult::FAILED:
                doesTestExist = true;
                goto breakEndOfFor;

            case TestResult::INPUT_ERROR:
                testInputIsCorrect = false;
                printf("TEST INPUT IS INCORRECT\n");
                goto breakEndOfWhile;

            case TestResult::WRONG_TEST:
                break;

            default:
                assert(false && "autoTest::runTest()'s return is not a TestResult's member");
            }
        }
    breakEndOfFor:;

        if (!doesTestExist) {
            printf("Test '%s' does not exist\n", command);
        }
    }
breakEndOfWhile:;

    if (autoTest::closeTestFile(testFile) != 0) {
        printf("CANNOT CLOSE TEST FILE CORRECTLY\n");
    }

    if (testInputIsCorrect) {
        printf("TESTS ARE DONE\n");
    }

    return 0;
}
