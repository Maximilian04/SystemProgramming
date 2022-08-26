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

#include "testingSystem\TestResult.h"

const int MAX_FUNC_NAME_LENGTH = 64;  ///< Size of string buffer for function is tested or for enum key in test
#define MAX_FUNC_NAME_LENGTH_STR "64" ///< Size of string buffer for function is tested or for enum key in test

const int NUMBER_OF_TEST_FUNCS = 2; ///< Total number of tests

namespace test {
    /**
     * @brief Structure with information about one test
     *
     * Includes pointer to testing function and its name
     */
    struct TestFuncInfo {
        TestResult(* const func)(FILE*); ///< Testing function
        const char* name;                ///< Name of testing function
    };

    TestResult strLib_strlen(FILE* inputFile);
    TestResult strLib_strncpy(FILE* inputFile);

    extern const TestFuncInfo testFuncList[NUMBER_OF_TEST_FUNCS];
}

#endif // TESTS_H
