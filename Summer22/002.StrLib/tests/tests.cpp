#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "compareDouble.h"

#include "strLib.h"

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
    TestResult strLib_strlen(FILE* inputFile) {
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
            "quadrEquation_solve", params.str,
            params.resultAns,
            result);
        return TestResult::FAILED;
    }

    /**
     * @brief Tests function
     *
     * **Function**:
     * char* strLib::strncpy(char* dst, const char* src, int count);
     *
     * @param [in] inputFile File with test
     * @return TestResult Result of testing
     */
    TestResult strLib_strncpy(FILE* inputFile) {
        struct {
            char src[MAX_FUNC_NAME_LENGTH];
            int count;
            char* resultAns;
        } params = {};

        // ------------- read params -------------

        int strKey = 0;
        SCAN(" [%d]", &strKey);
        SCANREAD(params.src, strKey);

        SCAN("%d", &params.count);
        // resultAns = dst

        // ------------- read params -------------
        // test function

        char dst[MAX_FUNC_NAME_LENGTH] = {};
        params.resultAns = dst;
        char* result = strLib::strncpy(dst, params.src, params.count);

        if (
            (result == params.resultAns) &&
            (strncmp(dst, params.src, params.count) == 0) &&
            (dst[params.count] == '\0')) {
            return TestResult::PASSED;
        }

        printf("TEST FAILED : %s: input: %s, %d\n"
            "       expected output: %s\n"
            "       got      output: %s\n",
            "quadrEquation_solve", params.src, params.count,
            params.resultAns,
            result);
        return TestResult::FAILED;
    }

    const TestFuncInfo testFuncList[NUMBER_OF_TEST_FUNCS] = {
        { FUNC_TO_TEST_LIST(strLib_strlen) },
        { FUNC_TO_TEST_LIST(strLib_strncpy) },
    };
}
