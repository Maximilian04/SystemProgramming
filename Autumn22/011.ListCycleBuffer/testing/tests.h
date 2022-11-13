#include <assert.h>

#include <testingSystem.h>

#define NUMBER_OF_TEST_FUNCS (1)

TestResult list_pushBack(FILE* inputFile);

const test::TestFuncInfo test::testFuncList[NUMBER_OF_TEST_FUNCS] = {
    { list_pushBack, "pushBack" },
};

#define SCAN(STR, ADDR)                       \
{                                              \
        if (fscanf(inputFile, STR, ADDR) < 1) { \
        return TestResult::INPUT_ERROR;          \
    }                                             \
}

#define SCANREAD(ADDR, N)                            \
{                                                     \
        if ((int)fread(ADDR, 1, N, inputFile) < (N)) { \
        return TestResult::INPUT_ERROR;                 \
    }                                                    \
}

TestResult list_pushBack(FILE* inputFile) {
    assert(inputFile != nullptr);

    return TestResult::PASSED;
}
