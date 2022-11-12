#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "autoTest.h"

namespace autoTest {
    /**
     * @brief Open file from cmd arguments or standart file
     *
     * @param [in] hasSpecialFile If user set file with tests
     * @param [in] userFileName (=nullptr) Name of user's file if hasSpecialFile is set to true
     * @return FILE* Opened file
     */
    FILE* openTestFile(bool hasSpecialFile, const char* userFileName) {
        if (hasSpecialFile) {
            assert(userFileName != nullptr);

            FILE* file = fopen(userFileName, "r");

            if (file != NULL) {
                return file;
            }
            printf("Cannot open file, run standart tests\n");
        }

        const char* fileName = "tests/standartTests.txt";
        FILE* file = fopen(fileName, "r");

        if (file != NULL) {
            return file;
        }

        assert(false && "Cannot open standartTests.txt");
        return nullptr;
    }

    /**
     * @brief Close file with tests (or NOT close stdin)
     *
     * @param [out] testFile File with tests
     * @return int Result of fclose()
     */
    int closeTestFile(FILE* testFile) {
        assert(testFile != nullptr);
        if (testFile == stdin) {
            return 0;
        }
        return fclose(testFile);
    }

    /**
     * @brief Runs test from **FILE** for **name** function if **name** is equal with **command**
     *
     * @param [in] testFunction Function for being tested
     * @param [in] name Name of function is tested
     * @param [in] command Command for current position in **FILE**
     * @param [in] testFile File with tests
     * @return TestResult Result of the test OR Input error OR wrong test notification
     * @warning Returns **true** whether or no test is passed
     */
    TestResult runTest(TestResult(*testFunction) (FILE* inputFile), const char* name, char* command, FILE* testFile) {
        assert(testFunction != nullptr);
        assert(name != nullptr);
        assert(command != nullptr);

        if (strcmp(command, name) == 0) {
            switch (testFunction(testFile)) {
            case TestResult::PASSED:
                return TestResult::PASSED;
            case TestResult::FAILED:
                return TestResult::FAILED;
                break;
            case TestResult::INPUT_ERROR:
                return TestResult::INPUT_ERROR;
                break;
            case TestResult::WRONG_TEST:
            default:
                assert(false && "testFunction()'s return is not a TestResult's member OR forbidden member");
            };
        }

        return TestResult::WRONG_TEST;
    }
}
