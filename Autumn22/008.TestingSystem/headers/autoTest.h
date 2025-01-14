/**
 * @file autoTest.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Functions for running tests from files
 * @date 2022-08-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef AUTOTEST_H
#define AUTOTEST_H

#include "TestResult.h"

namespace autoTest {
    FILE* openTestFile(bool hasSpecialFile, const char* userFileName = nullptr);
    int closeTestFile(FILE* testFile);

    TestResult runTest(TestResult(*testFunction) (FILE* inputFile), const char* name, char* command, FILE* testFile);
}

#endif // AUTOTEST_H
