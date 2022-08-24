/**
 * @file tests.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Tests for QuadrEquation project
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TESTS_H
#define TESTS_H

#include "QuadrEquation.h"

#include "TestResult.h"

const int MAX_FUNC_NAME_LENGTH = 64; ///< Size of string buffer for function is tested

namespace test {
    TestResult quadrEquation_solve(FILE* inputFile);
}

#endif // TESTS_H
