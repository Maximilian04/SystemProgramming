/**
 * @file tests.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Tests for QuadrEquation project
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "QuadrEquation.h"

#include "TestResult.h"

#define MAX_FUNC_NAME_LENGTH 64

namespace test {
    TestResult quadrEquation_solve(FILE* inputFile);
}
