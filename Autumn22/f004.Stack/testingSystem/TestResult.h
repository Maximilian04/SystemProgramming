/**
 * @file TestResult.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Test states
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TESTRESULT_H
#define TESTRESULT_H

/**
 * @brief Possible result of testing
 * 
 * Also WRONG_TEST for autoTest::runTest()
 * 
 */
enum TestResult {
    FAILED = 0,
    PASSED,
    INPUT_ERROR,
    WRONG_TEST,
};

#endif // TESTRESULT_H
