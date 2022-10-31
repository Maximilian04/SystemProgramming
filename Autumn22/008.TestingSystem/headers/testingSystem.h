/**
 * @file testingSystem.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Testing system
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TESTINGSYSTEM_H
#define TESTINGSYSTEM_H

#include <stdio.h>
#include "..\..\009.cmdParser\headers\cmdParser.h"
#include <cmdParser.h>

#include "TestResult.h"

namespace testingSystem {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,    ///< No errors, program had to continue
        FLAGS_ERR, ///< Error in flags sequence
    };

    Error main(int argc, const char* const* const argv);
}

#ifndef NUMBER_OF_TEST_FUNC
/// Total number of tests
#define NUMBER_OF_TEST_FUNCS (1)
#endif // NUMBER_OF_TEST_FUNC

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

    //TestResult strLib_strlen (FILE* inputFile);

    extern const TestFuncInfo testFuncList[NUMBER_OF_TEST_FUNCS];
}

#endif // TESTINGSYSTEM_H
