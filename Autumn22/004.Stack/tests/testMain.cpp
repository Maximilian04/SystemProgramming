#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "testingSystem\testUI.h"
#include "tests.h"

#include "stack\Stack.h"
#include "logger\logger.h"

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

    // ------------------------------ logging ------------------------------
    logger::emergencyLog("<font color=\"MistyRose\">Hello log</font>");
    Stack stack = {};
    STACK__ctor(stack), 1);
    //STACK__dump(stack));
    stack::resize(&stack, 0);
    //STACK__dump(stack));
    stack::push(&stack, 8);
    //STACK__dump(stack));
    stack::push(&stack, 7);
    //STACK__dump(stack));
    stack::push(&stack, 6);
    //STACK__dump(stack));
    stack::push(&stack, 5);
    //STACK__dump(stack));
    int var = 0;
    stack::pop(&stack, &var);
    //STACK__dump(stack));
    stack::pop(&stack);
    //STACK__dump(stack));
    stack::push(&stack, 7);
    //STACK__dump(stack));
    stack::push(&stack, 6);
    //STACK__dump(stack));
    stack::push(&stack, 5);
    //STACK__dump(stack));
    stack::push(&stack, 93);
    //STACK__dump(stack));
    stack::pop(&stack);
    //STACK__dump(stack));
    stack::pop(&stack);
    //STACK__dump(stack));
    stack::pop(&stack);
    //STACK__dump(stack));
    stack::push(&stack, 94);
    //STACK__dump(stack));
    stack::pop(&stack);
    //stack.data[5] = 8;
    //stack.canaryEnd++;
    //STACK__dump(stack));
    stack::push(&stack, 96);
    //STACK__dump(stack));
    stack::pop(&stack);
    //STACK__dump(stack));
    stack::resize(&stack, 2);
    //stack::pop(nullptr);
    //STACK__dump(stack));
    // ------------------------------ logging ------------------------------

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

    return 0;
}
