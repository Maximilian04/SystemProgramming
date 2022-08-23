#include <stdio.h>

#include "compareDouble.h"
#include "QuadrEquation.h"

#define TEST(VALUE) \
    if (!(VALUE)) { \
    printf("TEST FAILED : %s\n", #VALUE); \
    }


bool test_quadrEquation_solve(double a, double b, double c, int resultAns, double root1Ans, double root2Ans);
