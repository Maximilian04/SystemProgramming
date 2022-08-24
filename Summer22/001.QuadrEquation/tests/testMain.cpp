#include <stdio.h>

#include "autoTest.h"
#include "tests.h"

#define FUNC_TO_TEST(FUNC) &test::FUNC, #FUNC

int main(int argc, char** argv) {
    FILE* testFile = autoTest::openTestFile(argc, argv);

    char command[MAX_FUNC_NAME_LENGTH];

    while (fscanf(testFile, "%s", command) != EOF) {

        if (!autoTest::runTest(FUNC_TO_TEST(quadrEquation_solve), command, testFile)) {
            printf("TEST INPUT IS INCORRECT");
            return 0;
        }
    }

    printf("TESTS ARE DONE\n");
    return 0;
}
