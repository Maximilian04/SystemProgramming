#include "quadrEquation.h"

#include <stdio.h>
#include <cassert>

int main() {
    QuadrEquation equation;
    printf("Print coefficients for \"a*x^2 + b*x + c = 0\" equation: \n");
    quadrEquation::scan(&equation);

    double root1 = 0;
    double root2 = 0;
    switch (quadrEquation::solve(&equation, &root1, &root2)) {
    case quadrEquation::NumberOfRoots::NO_ROOTS:
        printf("No roots\n");
        break;
    case quadrEquation::NumberOfRoots::ONE_ROOT:
        printf("Root: %lg\n", root1);
        break;
    case quadrEquation::NumberOfRoots::TWO_ROOTS:
        printf("Roots: %lg, %lg\n", root1, root2);
        break;
    case quadrEquation::NumberOfRoots::INF_ROOTS:
        printf("Any number is a root\n");
        break;
    default:
        assert(false && "quadrEquation()'s return is not a NumberOfRoots'es member");
    }

    return 0;
}
