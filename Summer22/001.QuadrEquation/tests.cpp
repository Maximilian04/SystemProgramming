#include "tests.h"

// quadrEquation::NumberOfRoots quadrEquation::solve(QuadrEquation* equation, double* root1, double* root2);
bool test_quadrEquation_solve(double a, double b, double c, int resultAns, double root1Ans, double root2Ans) {
    QuadrEquation equation = {};
    equation.a = a;
    equation.b = b;
    equation.c = c;
    double root1 = 0;
    double root2 = 0;
    quadrEquation::NumberOfRoots result = quadrEquation::solve(&equation, &root1, &root2);

    return
        compareDouble(result, resultAns) &&
        compareDouble(root1, root1Ans) &&
        compareDouble(root2, root2Ans);
}

int main() {
    TEST(test_quadrEquation_solve(1, 1,  1, quadrEquation::NumberOfRoots::NO_ROOTS,   0, 0));
    TEST(test_quadrEquation_solve(1, 0,  0, quadrEquation::NumberOfRoots::ONE_ROOT,   0, 0));
    TEST(test_quadrEquation_solve(1, 0, -1, quadrEquation::NumberOfRoots::TWO_ROOTS, -1, 1));
    TEST(test_quadrEquation_solve(0, 0,  0, quadrEquation::NumberOfRoots::INF_ROOTS,  0, 0));

    printf("TESTS ARE DONE\n");
    return 0;
}
