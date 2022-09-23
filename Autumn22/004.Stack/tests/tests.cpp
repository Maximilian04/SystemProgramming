#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tests.h"
#include "compareDouble.h"

#define SCAN(STR, ADDR)                                \
{                                                      \
        if (fscanf(inputFile, STR, ADDR) < 1) {        \
        return TestResult::INPUT_ERROR;                \
    }                                                  \
}

#define SCANREAD(ADDR, N)                              \
{                                                      \
        if ((int)fread(ADDR, 1, N, inputFile) < (N)) { \
        return TestResult::INPUT_ERROR;                \
    }                                                  \
}

#define FUNC_TO_TEST_LIST(FUNC) FUNC, #FUNC

namespace test {
    /**
     * @brief Tests function
     *
     * **Function**:
     * int strLib::strlen(const char* str);
     *
     * @param [in] inputFile File with test
     * @return TestResult Result of testing
     */
    /*TestResult strLib_strlen(FILE* inputFile) {
        struct {
            char str[MAX_FUNC_NAME_LENGTH];
            int resultAns;
        } params = {};

        // ------------- read params -------------

        int strKey = 0;
        SCAN(" [%d]", &strKey);
        SCANREAD(params.str, strKey);

        SCAN("%d", &params.resultAns);

        // ------------- read params -------------
        // test function

        int result = strLib::strlen(params.str);

        if (
            (result == params.resultAns)) {
            return TestResult::PASSED;
        }

        printf("TEST FAILED : %s: input: %s\n"
            "       expected output: %d\n"
            "       got      output: %d\n",
            "strLib_strlen", params.str,
            params.resultAns,
            result);
        return TestResult::FAILED;
    }*/

    /**
     * @brief Tests function
     *
     * Do some action
     *
     * @param [in] inputFile File with test
     * @return TestResult Result of testing
     */
    TestResult stack_do_test(FILE* inputFile) {
        assert(inputFile != nullptr);

        struct {
            char command[MAX_FUNC_NAME_LENGTH];
            int resultAns;
        } params = {};

        // ------------- read params -------------

        int strKey = 0;
        SCAN(" [%d]", &strKey);
        SCANREAD(params.command, strKey);

        params.resultAns = 0;

        // ------------- read params -------------
        // test function

        int result = 0; //strLib::strlen(params.str);

        if (
            (result == params.resultAns)) {
            return TestResult::PASSED;
        }

        printf("TEST FAILED : %s: input: %s\n"
            "       expected output: %d\n"
            "       got      output: %d\n",
            "stack_do_test", params.command,
            params.resultAns,
            result);
        return TestResult::FAILED;
    }

    const TestFuncInfo testFuncList[NUMBER_OF_TEST_FUNCS] = {
        { FUNC_TO_TEST_LIST(stack_do_test)  },
    };
}
