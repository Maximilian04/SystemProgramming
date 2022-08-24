#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "compareDouble.h"

#define SCAN(STR, ADDR)                                \
{                                                      \
        if (fscanf(inputFile, STR, ADDR) < 1) {        \
        return TestResult::INPUT_ERROR;                \
    }                                                  \
}

namespace test {
    /**
     * @brief Tests function
     *
     * **Function**:
     * quadrEquation::NumberOfRoots quadrEquation::solve(QuadrEquation* equation, double* root1, double* root2);
     * 
     * Reads test parameters from file
     *
     * @param [in] inputFile File with test
     * @return TestResult Result of testing
     */
    TestResult quadrEquation_solve(FILE* inputFile) {
        struct {
            double a;
            double b;
            double c;
            quadrEquation::NumberOfRoots resultAns;
            double root1Ans;
            double root2Ans;
        } params = {};

        // ------------- read params -------------

        SCAN("%lg", &params.a);
        SCAN("%lg", &params.b);
        SCAN("%lg", &params.c);
        char resultAnsKey[MAX_FUNC_NAME_LENGTH];
        SCAN("%s", resultAnsKey);
        if (strcmp("NO_ROOTS", resultAnsKey) == 0) {
            params.resultAns = quadrEquation::NumberOfRoots::NO_ROOTS;
        } else if (strcmp("ONE_ROOT", resultAnsKey) == 0) {
            params.resultAns = quadrEquation::NumberOfRoots::ONE_ROOT;
        } else if (strcmp("TWO_ROOTS", resultAnsKey) == 0) {
            params.resultAns = quadrEquation::NumberOfRoots::TWO_ROOTS;
        } else if (strcmp("INF_ROOTS", resultAnsKey) == 0) {
            params.resultAns = quadrEquation::NumberOfRoots::INF_ROOTS;
        } else {
            return TestResult::INPUT_ERROR;
        }
        SCAN("%lg", &params.root1Ans);
        SCAN("%lg", &params.root2Ans);

        // ------------- read params -------------
        // test function

        QuadrEquation equation = {};
        equation.a = params.a;
        equation.b = params.b;
        equation.c = params.c;
        double root1 = 0;
        double root2 = 0;
        quadrEquation::NumberOfRoots result = quadrEquation::solve(&equation, &root1, &root2);

        /*if (
            (result == params.resultAns ? true : (printf("got wrong result\n"), false)) &&
            (compareDouble(root1, params.root1Ans) ? true : (printf("got %lg expected %lg as root1\n", root1, params.root1Ans), false)) &&
            (compareDouble(root2, params.root2Ans) ? true : (printf("got %lg expected %lg as root2\n", root2, params.root2Ans), false))) {
            return TestResult::PASSED;
        }*/
        if (
            (result == params.resultAns) &&
            (compareDouble(root1, params.root1Ans)) &&
            (compareDouble(root2, params.root2Ans))) {
            return TestResult::PASSED;
        }

        printf("TEST FAILED : %s: input: %lg, %lg, %lg\n"
            "       expected output: %d, %lg, %lg\n"
            "       got      output: %d, %lg, %lg\n",
            "quadrEquation_solve", params.a, params.b, params.c,
            params.resultAns, params.root1Ans, params.root2Ans,
            result, root1, root2);
        return TestResult::FAILED;
    }
}
