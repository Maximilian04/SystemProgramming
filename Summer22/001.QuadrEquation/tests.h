/**
 * @file tests.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Tests for QuadrEquation project
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

#include "compareDouble.h"
#include "QuadrEquation.h"

/**
 * @brief Alerts if **VALUE** is false
 * 
 * Use it like TEST(test_function(params..., answers...))
 * 
 */
#define TEST(VALUE)                           \
{                                             \
    if (!(VALUE)) {                           \
        printf("TEST FAILED : %s\n", #VALUE); \
    }                                         \
}

bool test_quadrEquation_solve(double a, double b, double c, int resultAns, double root1Ans, double root2Ans);
