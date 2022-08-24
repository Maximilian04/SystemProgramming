#include <string.h>
#include <stdio.h>
#include <cassert>

#include "autoTest.h"

namespace autoTest {
    FILE* openTestFile(int argc, char** argv) {
        if (argc > 1) {
            const char* fileName = argv[1];
            FILE* file = fopen(fileName, "r");

            if (file != NULL) {
                return file;
            }
            printf("Cannot open file, run standart tests");
        }

        const char* fileName = "tests/standartTests.txt";
        FILE* file = fopen(fileName, "r");

        if (file != NULL) {
            return file;
        }

        assert(false && "Cannot open standartText.txt");
        return nullptr;
    }

    bool runTest(TestResult(*testFunction) (FILE* inputFile), const char* name, char* command, FILE* testFile) {
        if (strcmp(command, name) == 0) {
            switch (testFunction(testFile)) {
            case TestResult::PASSED:
            case TestResult::FAILED:
                return true;
                break;
            case TestResult::INPUT_ERROR:
                return false;
                break;
            default:
                assert(false && "testFunction()'s return is not a TestResult's member");
            };
        }

        return true;
    }
}
