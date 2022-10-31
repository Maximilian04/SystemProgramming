#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "testingSystem.h"

#include "autoTest.h"

namespace testingSystem {
    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
    cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata);
    void printHelpMessage();

    const size_t MAX_FUNC_NAME_LENGTH = 64;

    /**
     * @brief Struct for transfering information to cmdParser::processFlags
     *
     */
    typedef struct {
        FILE** testFilePtr;  ///< buffer with user's tests file's name
    } ProccessFlagsPtrs;

    Error main(int argc, const char* const* const argv) {
        FILE* testFile = nullptr;

        ProccessFlagsPtrs proccessFlagsPtrs = {
            &testFile
        };

        switch (cmdParser::handleFlags(argc, argv, reactToFlags, &proccessFlagsPtrs)) {
        case cmdParser::ParserResult::BAD_INPUT:
            return Error::FLAGS_ERR;
            break;
        case cmdParser::ParserResult::GOOD_INPUT:
            break;
        default:
            assert(false && "cmdParser::processFlags()'s return value is not an allowed cmdParser::PARSER_RESULT's member");
            break;
        }

        char command[MAX_FUNC_NAME_LENGTH] = {};
        bool testInputIsCorrect = true;

        while (fscanf(testFile, "%s", command) != EOF) {
            bool doesTestExist = false;

            if (strcmp(command, "exit") == 0) {
                break;
            }

            for (const test::TestFuncInfo testFunc : test::testFuncList) {
                switch (autoTest::runTest(testFunc.func, testFunc.name, command, testFile)) {
                case TestResult::PASSED:
                case TestResult::FAILED:
                    doesTestExist = true;
                    break;

                case TestResult::INPUT_ERROR:
                    testInputIsCorrect = false;
                    printf("'%s' TEST INPUT IS INCORRECT\n", testFunc.name);
                    goto errorTestInput;

                case TestResult::WRONG_TEST:
                    break;

                default:
                    assert(false && "autoTest::runTest()'s return is not a TestResult's member");
                }

                if (doesTestExist) {
                    break;
                }
            }

            if (!doesTestExist) {
                printf("Test '%s' does not exist\n", command);
            }
        }
    errorTestInput:;

        if (autoTest::closeTestFile(testFile) != 0) {
            printf("CANNOT CLOSE TEST FILE CORRECTLY\n");
        }

        if (testInputIsCorrect) {
            printf("TESTS ARE DONE\n");
        }

        return Error::OK;
    }

    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata) {
        cmdParser::ParserResult res = cmdParser::standartReactToFlags(cmdFlagC, cmdArguments, userdata, printHelpMessage, handleFlag);
        if (res) return res;

        if (*((ProccessFlagsPtrs*)userdata)->testFilePtr == nullptr) {
            *((ProccessFlagsPtrs*)userdata)->testFilePtr = autoTest::openTestFile(false);
        }
        return cmdParser::ParserResult::GOOD_INPUT;
    }

    cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata) {
        assert(userdata != nullptr);

        switch (cmdArgument.key) {
        case 'f':
            if (!cmdArgument.hasArgument) {
                printf("Cannot recognize file name after '-f'. Please use flags from list below.\n");
                printHelpMessage();
                return cmdParser::handleFlagResult::INCORRECT_INPUT;
            }

            *((ProccessFlagsPtrs*)userdata)->testFilePtr = autoTest::openTestFile(true, cmdArgument.argument);
            break;
        case 'i':
            *((ProccessFlagsPtrs*)userdata)->testFilePtr = stdin;
            break;
        default:
            return cmdParser::handleFlagResult::UNKNOWN;
        }

        return cmdParser::handleFlagResult::KNOWN;
    }

    /**
     * @brief Prints help message to the console
     *
     */
    void printHelpMessage() {
        printf(
            "Help message. Command list:\n"
            "-h\t\tshow help message\n"
            "-f [name]\trun tests from [name] file\n"
            "-i\t\tallow you to enter test line via console\n");
    }
}
